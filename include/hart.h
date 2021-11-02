#ifndef HART_H_
#define HART_H_

#include "config.h"
#include "virtual_mem.h"
#include "instruction.h"

namespace risc
{
    class Hart
    {
        RegValue regs_[RegFileGprSize]{0};

        RegValue pc_      = 0;
        RegValue next_pc_ = 0;
        
        VirtualMem& memory_;
        VirtAddr entry_;

    public:

        Hart(VirtualMem& virt_mem, VirtAddr entry);

        RegValue get_reg(RegId id) const;
        RegValue& operator[](RegId id);
        void set_reg(RegId id, RegValue value);
        
        RegValue get_pc() const;
        
        RegValue branch(RegValue target);

        bool read (VirtAddr virt_address, size_t size, RegValue* value);
        bool write(VirtAddr virt_address, size_t size, RegValue  value);
        
        bool execute();
    };
}


#endif // !HART_H_
