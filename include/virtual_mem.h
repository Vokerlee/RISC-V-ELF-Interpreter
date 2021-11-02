#ifndef VIRT_MEM_H_
#define VIRT_MEM_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <elf.h>
#include <gelf.h>
#include <libelf.h> 

#include "phys_page.h"
#include "config.h"

namespace risc
{
    class PhysAddr
    {
    public:

        PhysPage* page_;
        PhysPageOffset offset_;

        PhysAddr(PhysPage* page = nullptr, PhysPageOffset offset = 0);

        bool operator==(const PhysAddr& rhs) const;
        bool operator!=(const PhysAddr& rhs) const;

        bool is_zero() const;
    };

    class VirtualMem
    {
        std::vector<PhysPage *> page_table_; // page table
        std::list<PhysPage *> alloc_pages_;  // to control all allocated pages

        VirtAddr stack_addr_;

        bool is_valid_ = true;

        bool allocate_page(VirtAddr virt_address);   
        PhysAddr get_phys_addr(VirtAddr virt_address) const;

        size_t count_pages(VirtAddr start, VirtAddr end) const;
        size_t next_page_offset(VirtAddr address) const;

    public:

        VirtualMem(size_t virt_mem_size = kVirtMemSize, VirtAddr stack_address = kDefaultStackAddress);
        ~VirtualMem();

        bool read (VirtAddr virt_address, size_t size, RegValue* value) const;
        bool write(VirtAddr virt_address, size_t size, RegValue  value);

        VirtAddr get_stack_addr() const;

        bool load_elf_file(int elf_fd, GElf_Phdr* phdrs, GElf_Ehdr ehdr);

        bool is_valid() const;
    };
}

#endif // !VIRT_MEM_H_
