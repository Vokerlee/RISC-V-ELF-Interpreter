#ifndef PHYS_MEM_H_
#define PHYS_MEM_H_

#include <fstream>
#include <iostream>
#include "config.h"

namespace risc
{
    class VirtualMem;

    class PhysPage
    {
        size_t mem_size_;
        uint8_t* memory_;

        friend class VirtualMem;

    public:

        PhysPage(size_t mem_size = kPhysPageSize);
        ~PhysPage();

        PhysPage& operator=(PhysPage& rhs) = delete;
        PhysPage(const PhysPage& rhs) = delete;

        bool write(PhysPageOffset addr, size_t size, RegValue  value);
        bool read (PhysPageOffset addr, size_t size, RegValue* value) const;
    
        void dump(std::ostream& fout = std::cout) const;
    };

}

#endif // !PHYS_MEM_H_
