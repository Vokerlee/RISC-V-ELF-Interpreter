#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <elf.h>
#include <gelf.h>
#include <libelf.h> 
#include <assert.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "phys_page.h"
#include "config.h"
#include "virtual_mem.h"

using namespace risc;

PhysAddr::PhysAddr(PhysPage* page, PhysPageOffset offset) :
    page_(page),
    offset_(offset)
{}

bool PhysAddr::operator==(const PhysAddr& rhs) const
{
    if (offset_ == rhs.offset_ && page_ == rhs.page_)
        return true;
    else
        return false;
}

bool PhysAddr::operator!=(const PhysAddr& rhs) const
{
    return !operator==(rhs);
}

bool PhysAddr::is_zero() const
{
    if (*this == PhysAddr())
        return true;
    else
        return false;
}

bool VirtualMem::allocate_page(VirtAddr virt_address)
{
    VirtAddr offset = virt_address & kOffsetMask;
    VirtAddr index_table = (virt_address - offset) >> kNOffsetBits;

    if (page_table_[index_table] != nullptr)
        return true;

    PhysPage* page = new PhysPage(kPhysPageSize);
    if (page == nullptr)
        return false;

    page_table_[index_table] = page;
    alloc_pages_.push_back(page);           

    return true; 
}        

PhysAddr VirtualMem::get_phys_addr(VirtAddr virt_address) const
{
    VirtAddr offset = virt_address & kOffsetMask;
    VirtAddr index_table = (virt_address - offset) >> kNOffsetBits;

    if (page_table_[index_table] == nullptr) // page is not allocated
        return PhysAddr(); // zero address
    else
        return PhysAddr(page_table_[index_table], offset);

    return PhysAddr();       
}

size_t VirtualMem::count_pages(VirtAddr start, VirtAddr end) const
{
    size_t occupied_pages  = 0;
    size_t remainder_start = start % kPhysPageSize;
    size_t remainder_end   = end   % kPhysPageSize;

    if (start / kPhysPageSize == end / kPhysPageSize)
        return 1;

    size_t temp_start = start;
    size_t temp_end   = end;

    if (remainder_start != 0)
    {
        occupied_pages++;
        temp_start += kPhysPageSize - remainder_start;
    }

    if (remainder_end != 0)
    {
        occupied_pages++;
        temp_end -= remainder_end;
    }

    occupied_pages += (temp_end - temp_start) / kPhysPageSize;
    assert((temp_end - temp_start) % kPhysPageSize == 0);

    return occupied_pages;
}

size_t VirtualMem::next_page_offset(VirtAddr address) const
{
    size_t remainder = address % kPhysPageSize;
    return kPhysPageSize - remainder;
}

VirtualMem::VirtualMem(size_t virt_mem_size, VirtAddr stack_address) :
    page_table_(virt_mem_size / kPhysPageSize, nullptr),
    stack_addr_(stack_address)
{
    bool stack_alloc_state = allocate_page(stack_address);
    if (stack_alloc_state == false)
        is_valid_ = false;
}

VirtualMem::~VirtualMem()
{
    for (auto page: alloc_pages_)
        delete page;
}

bool VirtualMem::read(VirtAddr virt_address, size_t size, RegValue* value) const
{
    if (is_valid() == false)
        return false;

    if (value == nullptr)
        return false;

    switch (size)
    {
        case 0x1:
        case 0x2:
        case 0x4:
        {
            PhysAddr phys_addr = get_phys_addr(virt_address);
            if (phys_addr.is_zero())
                return false;

            return phys_addr.page_->read(phys_addr.offset_, size, value);
        }
        default:
            return false;
    }

    assert(false);
    return false;
}

bool VirtualMem::write(VirtAddr virt_address, size_t size, RegValue value)
{
    if (is_valid() == false)
        return false;

    switch (size)
    {
        case 0x1:
        case 0x2:
        case 0x4:
        {
            PhysAddr phys_addr = get_phys_addr(virt_address);

            if (phys_addr.is_zero()) // page is not allocated => allocate page
            {
                if (allocate_page(virt_address) == false)
                    return false;

                phys_addr = get_phys_addr(virt_address);
            }

            return phys_addr.page_->write(phys_addr.offset_, size, value);
        }
        default:
            return false;
    }

    assert(false);
    return false;
}

bool VirtualMem::is_valid() const
{
    return is_valid_;
}

VirtAddr VirtualMem::get_stack_addr() const
{
    return stack_addr_;
}

bool VirtualMem::load_elf_file(int elf_fd, GElf_Phdr* phdrs, GElf_Ehdr ehdr)
{
    if (is_valid() == false)
        return false;

    if (phdrs == nullptr)
        return false;

    struct stat elf_stat = {0};

    int stat_err = fstat(elf_fd, &elf_stat);
    if (stat_err == -1)
    {
        perror("cannot get elf-file statistics");
        return false;
    }

    void *elf_file_buffer = mmap(NULL, elf_stat.st_size, PROT_READ, MAP_SHARED, elf_fd, 0);
    if (elf_file_buffer == NULL)
    {
        perror("mmap error");
        return false;
    }

    for (size_t i = 0; i < ehdr.e_phnum; ++i)
    {
        VirtAddr pseg_start = phdrs[i].p_vaddr;
        VirtAddr pseg_size  = phdrs[i].p_memsz;

        size_t occupied_pages = count_pages(pseg_start, pseg_start + pseg_size);

        for (size_t page_idx = 0; page_idx < occupied_pages; page_idx++) // memory allocation
        {
            bool alloc_status = false;  
            PhysAddr phys_addr = get_phys_addr(pseg_start + page_idx * kPhysPageSize);

            if (phys_addr.is_zero())
            {
                alloc_status = allocate_page(pseg_start + page_idx * kPhysPageSize);
                if (alloc_status == false)
                {
                    munmap(elf_file_buffer, elf_stat.st_size);
                    return false;
                }
            }
        }

        occupied_pages = count_pages(pseg_start, pseg_start + phdrs[i].p_filesz);
        
        VirtAddr virt_page_offset = get_phys_addr(pseg_start).offset_;
        size_t elf_file_offset = phdrs[i].p_offset; // the start of program segment

        if (occupied_pages > 1)
        {
            for (size_t page_idx = 0; page_idx < occupied_pages - 1; page_idx++) // loading elf to allocated memory
            {
                PhysAddr phys_addr = get_phys_addr(pseg_start + page_idx * kPhysPageSize);

                memcpy(phys_addr.page_->memory_ + virt_page_offset, (char *) elf_file_buffer + elf_file_offset, next_page_offset(virt_page_offset));
                elf_file_offset += next_page_offset(virt_page_offset);
                virt_page_offset = 0;
            }
            
            PhysAddr phys_addr = get_phys_addr(pseg_start + phdrs[i].p_filesz);
            memcpy(phys_addr.page_->memory_, (char *) elf_file_buffer + elf_file_offset, phys_addr.offset_);
        }
        else
        {
            PhysAddr phys_addr = get_phys_addr(pseg_start);
            memcpy(phys_addr.page_->memory_ + phys_addr.offset_, (char *) elf_file_buffer + elf_file_offset, phdrs[i].p_filesz);
        }
    }

    munmap(elf_file_buffer, elf_stat.st_size);

    return true;
    
}
