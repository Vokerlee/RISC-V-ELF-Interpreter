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
{
    regs_[2] = virt_mem.get_stack_addr();
}

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

        if (memory_.read(pc_, kInstrSize, &instr_code) == false) // fetching
            return false;

        Instruction instr(instr_code); // decoding
        if (instr.is_corrupted())
            break;
        
        next_pc_ = pc_ + kInstrSize;
        (*(instr.executor_))(this, instr);
        regs_[0] = 0; // x0 must always be zero
        pc_ = next_pc_;
    }

    return true;
}

bool Hart::read(VirtAddr virt_address, size_t size, RegValue* value)
{
    return memory_.read(virt_address, size, value);
}

bool Hart::write(VirtAddr virt_address, size_t size, RegValue value)
{
    return memory_.write(virt_address, size, value);
}
