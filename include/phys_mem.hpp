#ifndef PHYS_MEM_H_
#define PHYS_MEM_H_

#include <fstream>
#include "config.h"

namespace risc
{
    template <size_t MemSize = kPhysMemSize>
    class PhysMemory
    {
        uint8_t memory_[MemSize];

    public:

        bool write(PhysAddr addr, size_t size, RegValue value)
        {
            if (addr > (MemSize - size))
                return false;

            switch (size)
            {
                case 0x1:
                    memory_[addr] = value;
                    break;
                case 0x2:
                {
                    uint16_t * const new_mem = reinterpret_cast<uint16_t * const>(memory_ + addr);
                    new_mem[0] = value;
                    break;
                }
                case 0x4:
                {
                    uint32_t * const new_mem = reinterpret_cast<uint32_t * const>(memory_ + addr);
                    new_mem[0] = value;
                    break;
                }

                default:
                    return false;
            }

            return true;
        }

        bool read(PhysAddr addr, size_t size, RegValue* value)
        {
            if (value == nullptr)
                return false;
            if (addr > (MemSize - size))
                return false;

            switch (size)
            {
                case 0x1:
                    *value = memory_[addr];
                    break;
                case 0x2:
                {
                    uint16_t * const new_mem = reinterpret_cast<uint16_t * const>(memory_ + addr);
                    *value = new_mem[0];
                    break;
                }  
                case 0x4:
                    {
                    uint32_t * const new_mem = reinterpret_cast<uint32_t * const>(memory_ + addr);
                    *value = new_mem[0];
                    break;
                }
                
                default:
                    return false;
            }

            return true;
        }
    
        void dump(std::ostream& fout) const
        {
            fout << "Memory capacity: " << MemSize << std::endl;
            fout << "Memory dump:"      << std::endl;

            for (size_t i = 0; i < MemSize; ++i)
                fout << "byte №" << i << " = " << int(memory_[i]) << std::endl;
        }
    };

}

#endif // !PHYS_MEM_H_
