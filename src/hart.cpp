#include <bitset>
#include <iostream>
#include "config.h"
#include "virtual_mem.h"
#include "instruction.h"
#include "hart.h"

using namespace risc;

Hart::Hart(VirtualMem& virt_mem, VirtAddr entry) :
    memory_(virt_mem),
    entry_(entry)
{}

RegValue Hart::get_reg(RegId id) const
{
    return regs_[id];
}

RegValue& Hart::operator[](RegId id)
{
    return regs_[id];
}

void Hart::set_reg(RegId id, RegValue value)
{
    regs_[id] = value;
}

RegValue Hart::get_pc() const
{
    return pc_;
}

RegValue Hart::branch(RegValue target)
{
    return next_pc_ = target;
}

bool Hart::execute()
{
    pc_      = entry_;
    next_pc_ = entry_;

    while(true)
    {
        InstrValue instr_code = 0;

        if (memory_.read(pc_, kInstrSize, &instr_code) == false)
            return false;

        std::bitset<32> x(instr_code);
        std::cout << x << std::endl;
        
        Instruction instr(instr_code);
        if (instr.is_corrupted())
            break;
        
        next_pc_ = pc_ + kInstrSize;
        std::cout << "\nclass = " << instr.instr_class_ << std::endl;
        std::cout << "rs1 = " << instr.reg_src1_ << std::endl; 
        std::cout << "rs2 = " << instr.reg_src2_ << std::endl;
        std::cout << "rd  = " << instr.reg_dest_ << std::endl;
        std::cout << "imm = " << instr.immediate_ << std::endl;
        //insn.execute(this, insn);
        pc_ = next_pc_;
    }

    return true;
}
