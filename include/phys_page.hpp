#ifndef PHYS_MEM_H_
#define PHYS_MEM_H_

#include <fstream>
#include "config.h"

namespace risc
{
    class PhysPage
    {
        size_t mem_size_;
        uint8_t* memory_;

    public:

        PhysPage(size_t mem_size = kPhysPageSize) :
            mem_size_(mem_size)
        {
            memory_ = new uint8_t[mem_size]{};
        }

        ~PhysPage()
        {
            delete [] memory_;
        }

        PhysPage& operator=(PhysPage& rhs) = delete;
        PhysPage(const PhysPage& rhs) = delete;

        bool write(PhysPageOffset addr, size_t size, RegValue value)
        {
            if (addr > (mem_size_ - size))
                return false;
                
            switch (size)
            {
                case 0x1:
                case 0x2:
                case 0x4:
                    memcpy(memory_ + addr, &value, size);

                default:
                    return false;
            }

            return true;
        }

        bool read(PhysPageOffset addr, size_t size, RegValue* value)
        {
            if (value == nullptr)
                return false;
            if (addr > (mem_size_ - size))
                return false;

            switch (size)
            {
                case 0x1:
                case 0x2:
                case 0x4:
                    memcpy(value, memory_ + addr, size);
                
                default:
                    return false;
            }

            return true;
        }
    
        void dump(std::ostream& fout = std::cout) const
        {
            fout << "Memory capacity: " << mem_size_ << std::endl;
            fout << "Memory dump:"      << std::endl;

            for (size_t i = 0; i < mem_size_; ++i)
                fout << "byte #" << i << " = " << int(memory_[i]) << std::endl;
        }
    };

}

#endif // !PHYS_MEM_H_
