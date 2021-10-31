#ifndef HART_H_
#define HART_H_

#include "config.h"
#include "virtual_mem.h"
//#include "instruction.hpp"

namespace risc
{
    class Hart
    {
        RegValue regs_[RegFileGprSize];

        RegValue pc_;
        RegValue next_pc_;
        
        VirtualMem& memory_;

        VirtAddr entry_;

    public:

        Hart(VirtualMem& virt_mem, VirtAddr entry) :
            memory_(virt_mem),
            pc_(0),
            regs_{0},
            next_pc_(0),
            entry_(entry)
        {}

        RegValue get_reg(RegId id) const
        {
            return regs_[id];
        }

        RegValue& operator[](RegId id)
        {
            return regs_[id];
        }
        
        void set_reg(RegId id, RegValue value)
        {
            regs_[id] = value;
        }
        
        RegValue get_pc() const
        {
            return pc_;
        }
        
        RegValue branch(RegValue target)
        {
            return next_pc_ = target;
        }
        
        bool execute()
        {
            pc_      = entry_;
            next_pc_ = entry_;

            InstrValue instr_code = 0;

            if (memory_.read(pc_, kInstrSize, &instr_code) == false)
                return false;

            std::cout << std::hex << instr_code << std::endl;
            std::bitset<32> x(instr_code);
            std::cout << x << std::endl;

            // while(true)
            // {
            //     InstrValue instr_code = 0;

            //     if (memory_.read(pc_, kInstrSize, &instr_code) == false)
            //         return false;
                
            //     //Instruction insn(instr_code);
                
            //     next_pc_ = pc_ + kInstrSize;
            //     //insn.execute(this, insn);
            //     pc_ = next_pc_;
            // }

            return true;
        }
    };
}


#endif // !HART_H_
