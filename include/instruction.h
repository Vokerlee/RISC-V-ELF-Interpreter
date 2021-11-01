#ifndef INSTR_H_
#define INSTR_H_

#include "config.h"
#include "utils.hpp"

namespace risc
{
    class Instruction
    {
    public:
        //Executor executor_;
        InstrClass instr_class_ = RV32I_ERROR;

        RegId reg_dest_ = RegIdZero;
        RegId reg_src1_ = RegIdZero;
        RegId reg_src2_ = RegIdZero;

        RegValue immediate_ = 0;

        bool decode(InstrValue instr);

    public:
        Instruction(InstrValue instr);

        bool is_corrupted() const;
    };
}

#endif // !INSTR_H_
