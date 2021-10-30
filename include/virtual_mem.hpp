#ifndef VIRT_MEM_H_
#define VIRT_MEM_H_

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

#include "phys_page.hpp"
#include "config.h"

namespace risc
{
    class PhysAddr
    {
    public:

        PhysPage* page_;
        PhysPageOffset offset_;

        PhysAddr(PhysPage* page = nullptr, PhysPageOffset offset = 0) :
            page_(page),
            offset_(offset)
        {}

        bool operator==(const PhysAddr& rhs) const
        {
            if (offset_ == rhs.offset_ && page_ == rhs.page_)
                return true;
            else
                return false;
        }

        bool operator!=(const PhysAddr& rhs) const
        {
            return !operator==(rhs);
        }

        bool is_zero() const
        {
            if (*this == PhysAddr())
                return true;
            else
                return false;
        }
    };

    class VirtualMem
    {
        std::vector<PhysPage *> page_table_; // page table
        std::list<PhysPage *> alloc_pages_;  // to control all allocated pages

    public:

        VirtualMem(size_t virt_mem_size = kVirtMemSize) :
            page_table_(virt_mem_size / kPhysPageSize, nullptr)
        {
            
        }

        ~VirtualMem()
        {
            for (auto page: alloc_pages_)
                delete page;
        }

        bool read(VirtAddr virt_address, size_t size, RegValue* value)
        {
            if (value == nullptr)
                return false;

            std::cout << "read: virt_address = " << virt_address << std::endl; //////////
            PhysAddr phys_addr = get_phys_addr(virt_address);
            std::cout << "phys_addr = " << phys_addr.page_ << ", offset = " << phys_addr.offset_ << std::endl; 

            if (phys_addr.is_zero())
                return false;

            std::cout << "page exists: = " << phys_addr.page_ << ", offset = " << phys_addr.offset_ << std::endl; 

            return phys_addr.page_->read(phys_addr.offset_, size, value);
        }


        bool write(VirtAddr virt_address, size_t size, RegValue value)
        {
            std::cout << "write: virt_address = " << virt_address << std::endl; //////////
            PhysAddr phys_addr = get_phys_addr(virt_address);
            std::cout << "phys_addr = " << phys_addr.page_ << ", offset = " << phys_addr.offset_ << std::endl; 

            if (phys_addr.is_zero()) // page is not allocated => allocate page
            {
                std::cout << "write: not allocted page for virt_address = " << virt_address << std::endl; //////////
                if (allocate_page(virt_address) == false)
                    return false;

                std::cout << "write: successfully allocated page for virt_address = " << virt_address << std::endl; //////////

                phys_addr = get_phys_addr(virt_address);
            }

            return phys_addr.page_->write(phys_addr.offset_, size, value);
        }

        bool load_elf_file(int elf_fd, GElf_Phdr* phdrs, size_t phnum)
        {
            assert(phdrs);

            std::cout << "In loading eld program headers\n";
            std::cout << "There are n = " << phnum << " headers" << std::endl;

            for (size_t i = 0; i < phnum; ++i)
            {   
                std::cout << "My[" << i << "] filesize is " << phdrs[i].p_filesz << ", memsize is " << phdrs[i].p_memsz << std::endl;
            }

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

            for (size_t i = 0; i < phnum; ++i)
            {
                VirtAddr phdr_start = phdrs[i].p_vaddr;
                VirtAddr phdr_size  = phdrs[i].p_memsz;

                size_t occupied_pages = count_pages(phdr_start, phdr_start + phdr_size);


                for (size_t page_idx = 0; page_idx < occupied_pages; page_idx++)
                {
                    allocate_page()
                    memcpy()
                }
            }

            munmap(elf_file_buffer, elf_stat.st_size);



            return true;
            
        }

    private:

        bool allocate_page(VirtAddr virt_address)
        {
            VirtAddr offset = virt_address & kOffsetMask;
            VirtAddr index_table = (virt_address - offset) >> kNOffsetBits;

            PhysPage* page = new PhysPage(kPhysPageSize);
            if (page == nullptr)
                return false;

            page_table_[index_table] = page;
            alloc_pages_.push_back(page);           

            return true; 
        }        

        PhysAddr get_phys_addr(VirtAddr virt_address) const
        {
            VirtAddr offset = virt_address & kOffsetMask;
            VirtAddr index_table = (virt_address - offset) >> kNOffsetBits;

            if (page_table_[index_table] == nullptr) // page is not allocated
                return PhysAddr(); // zero address
            else
                return PhysAddr(page_table_[index_table], offset);

            return PhysAddr();       
        }

        size_t count_pages(VirtAddr start, VirtAddr end)
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
    };

}

#endif // !VIRT_MEM_H_
