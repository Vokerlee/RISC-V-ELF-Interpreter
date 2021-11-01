#ifndef INSTR_H_
#define INSTR_H_

#include "config.h"
#include "utils.hpp"
#include "executor.h"

namespace risc
{
    class Instruction
    {
    public:
        InstrClass instr_class_ = RV32I_ERROR;

        RegId reg_dest_ = RegIdZero;
        RegId reg_src1_ = RegIdZero;
        RegId reg_src2_ = RegIdZero;

        RegValue immediate_ = 0;

        bool decode(InstrValue instr);
        
        Executor* executor_ = nullptr;

    public:
        Instruction(InstrValue instr);
        ~Instruction();

        bool is_corrupted() const;
    };
}

#endif // !INSTR_H_
