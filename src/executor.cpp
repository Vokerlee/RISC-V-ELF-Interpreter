#include "config.h"
#include "utils.hpp"
#include "hart.h"
#include "instruction.h"
#include "executor.h"
#include <iostream>
#include <bitset>

const size_t BITS_PER_BYTE = 8;

using namespace risc;

bool ExecutorRV32I_LUI::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": lui x" << instr.reg_dest_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;
    
    hart->set_reg(instr.reg_dest_, instr.immediate_);

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_AUIPC::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": auipc x" << instr.reg_dest_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;
    
    hart->set_reg(instr.reg_dest_, instr.immediate_ + hart->get_pc());

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_JAL::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": jal x" << instr.reg_dest_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;
    
    hart->set_reg(instr.reg_dest_, hart->get_next_pc());
    hart->branch(hart->get_pc() + instr.immediate_);

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_JALR::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": jalr x" << instr.reg_dest_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << 
        "(x" << instr.reg_src1_ << ")" << std::endl;

    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    
    hart->set_reg(instr.reg_dest_, hart->get_next_pc());
    RegValue target = hart->get_reg(instr.reg_src1_) + instr.immediate_;
    RegValue mask = (1 << (BITS_PER_BYTE * sizeof(RegValue))) - 2;

    hart->branch(target & mask);

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_BEQ::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": beq x" << instr.reg_src2_ << ", x" << instr.reg_src1_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::cout << "x" << instr.reg_src2_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) << std::endl;

    if (hart->get_reg(instr.reg_src2_) == hart->get_reg(instr.reg_src1_))
        hart->branch(hart->get_pc() + instr.immediate_);

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_BNE::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": bne x" << instr.reg_src2_ << ", x" << instr.reg_src1_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::cout << "x" << instr.reg_src2_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) << std::endl;

    if (hart->get_reg(instr.reg_src2_) != hart->get_reg(instr.reg_src1_))
        hart->branch(hart->get_pc() + instr.immediate_);

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_BLT::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": blt x" << instr.reg_src2_ << ", x" << instr.reg_src1_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::cout << "x" << instr.reg_src2_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) << std::endl;

    if (static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) > static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)))
        hart->branch(hart->get_pc() + instr.immediate_);

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_BGE::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": bge x" << instr.reg_src2_ << ", x" << instr.reg_src1_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::cout << "x" << instr.reg_src2_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) << std::endl;

    if (static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) <= static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)))
        hart->branch(hart->get_pc() + instr.immediate_);

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_BLTU::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": bltu x" << instr.reg_src2_ << ", x" << instr.reg_src1_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::cout << "x" << instr.reg_src2_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) << std::endl;

    if (hart->get_reg(instr.reg_src2_) > hart->get_reg(instr.reg_src1_))
        hart->branch(hart->get_pc() + instr.immediate_);

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_BGEU::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": bgeu x" << instr.reg_src2_ << ", x" << instr.reg_src1_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::cout << "x" << instr.reg_src2_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) << std::endl;

    if (hart->get_reg(instr.reg_src2_) <= hart->get_reg(instr.reg_src1_))
        hart->branch(hart->get_pc() + instr.immediate_);

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_LB::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": lb x" << instr.reg_dest_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << "(x" << instr.reg_src1_ << ")" << std::endl;
        
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    std::cout << "before: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    RegValue load_byte{};
    if (hart->read(hart->get_reg(instr.reg_src1_) + instr.immediate_, 0x1, &load_byte) == false)
        return false;

    hart->set_reg(instr.reg_dest_, static_cast<SignedRegValue>(static_cast<SignedByte>(load_byte)));

    std::cout << "after: x" << instr.reg_dest_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;
    
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_LH::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": lh x" << instr.reg_dest_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << "(x" << instr.reg_src1_ << ")" << std::endl;
        
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    std::cout << "before: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    RegValue load_hword{};
    if (hart->read(hart->get_reg(instr.reg_src1_) + instr.immediate_, 0x2, &load_hword) == false)
        return false;

    hart->set_reg(instr.reg_dest_, static_cast<SignedRegValue>(static_cast<SignedHWord>(load_hword)));

    std::cout << "after: x" << instr.reg_dest_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;
    
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_LW::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": lw x" << instr.reg_dest_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << "(x" << instr.reg_src1_ << ")" << std::endl;
        
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    std::cout << "before: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    RegValue load_word{};
    if (hart->read(hart->get_reg(instr.reg_src1_) + instr.immediate_, 0x4, &load_word) == false)
        return false;

    hart->set_reg(instr.reg_dest_, static_cast<SignedRegValue>(load_word));

    std::cout << "after: x" << instr.reg_dest_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;
    
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_LBU::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": lbu x" << instr.reg_dest_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << "(x" << instr.reg_src1_ << ")" << std::endl;
        
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    std::cout << "before: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    RegValue load_byte{};
    if (hart->read(hart->get_reg(instr.reg_src1_) + instr.immediate_, 0x1, &load_byte) == false)
        return false;

    hart->set_reg(instr.reg_dest_, load_byte);

    std::cout << "after: x" << instr.reg_dest_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;
    
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_LHU::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": lhu x" << instr.reg_dest_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << "(x" << instr.reg_src1_ << ")" << std::endl;
        
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    std::cout << "before: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    RegValue load_hword{};
    if (hart->read(hart->get_reg(instr.reg_src1_) + instr.immediate_, 0x2, &load_hword) == false)
        return false;

    hart->set_reg(instr.reg_dest_, load_hword);

    std::cout << "after: x" << instr.reg_dest_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;
    
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SB::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": sb x" << instr.reg_src2_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << "(x" << instr.reg_src1_ << ")" << std::endl;

    std::cout << "x" << instr.reg_src2_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;

    if (hart->write(hart->get_reg(instr.reg_src1_) + instr.immediate_, 0x1, hart->get_reg(instr.reg_src2_)) == false)
        return false;

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SH::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": sh x" << instr.reg_src2_ <<
        ", "  << static_cast<SignedRegValue>(instr.immediate_) << "(x" << instr.reg_src1_ << ")" << std::endl;

    std::cout << "x" << instr.reg_src2_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;

    if (hart->write(hart->get_reg(instr.reg_src1_) + instr.immediate_, 0x2, hart->get_reg(instr.reg_src2_)) == false)
        return false;
        
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SW::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": sw x" << instr.reg_src2_ <<
         ", " << static_cast<SignedRegValue>(instr.immediate_) << "(x" << instr.reg_src1_ << ")" << std::endl;

    std::cout << "x" << instr.reg_src2_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;

    if (hart->write(hart->get_reg(instr.reg_src1_) + instr.immediate_, 0x4, hart->get_reg(instr.reg_src2_)) == false)
        return false;
        
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_ADDI::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": addi x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    std::cout << "before: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) + instr.immediate_);

    std::cout << "after: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SLTI::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": slti x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) << std::endl;
    std::cout << "before: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    if (static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) < static_cast<SignedRegValue>(instr.immediate_))
        hart->set_reg(instr.reg_dest_, 1);
    else
        hart->set_reg(instr.reg_dest_, 0);

    std::cout << "after: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SLTIU::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": sltiu x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", " << instr.immediate_ << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    std::cout << "before: x" << instr.reg_dest_  << " = " << hart->get_reg(instr.reg_dest_) << std::endl;

    if (hart->get_reg(instr.reg_src1_) < instr.immediate_)
        hart->set_reg(instr.reg_dest_, 1);
    else
        hart->set_reg(instr.reg_dest_, 0);

    std::cout << "after: x" << instr.reg_dest_  << " = " << hart->get_reg(instr.reg_dest_) << std::endl;
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_XORI::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": xori x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> imm(instr.immediate_);
    std::cout << instr.immediate_ << " = " << imm << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) ^ instr.immediate_);

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after: x" << instr.reg_dest_  << " = " << rd_after << std::endl;
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_ORI::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": ori x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> imm(instr.immediate_);
    std::cout << instr.immediate_ << " = " << imm << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) | instr.immediate_);

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after: x" << instr.reg_dest_  << " = " << rd_after << std::endl;
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_ANDI::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": andi x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> imm(instr.immediate_);
    std::cout << instr.immediate_ << " = " << imm << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) & instr.immediate_);

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after: x" << instr.reg_dest_  << " = " << rd_after << std::endl;
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SLLI::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": slli x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) << instr.immediate_);

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after: x" << instr.reg_dest_  << " = " << rd_after << std::endl;
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SRLI::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": srli x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) >> instr.immediate_);

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after: x" << instr.reg_dest_  << " = " << rd_after << std::endl;
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SRAI::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": srai x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", " << static_cast<SignedRegValue>(instr.immediate_) << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    SignedRegValue res = static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) >> static_cast<SignedRegValue>(instr.immediate_);
    hart->set_reg(instr.reg_dest_, static_cast<RegValue>(res));

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after: x" << instr.reg_dest_  << " = " << rd_after << std::endl;
    std::cout << std::endl;
    return true;
}

bool ExecutorRV32I_ADD::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": add x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", x" << instr.reg_src2_ << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    std::cout << "x" << instr.reg_src2_ << " = " << hart->get_reg(instr.reg_src2_) << std::endl;

    std::cout << "before: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) + hart->get_reg(instr.reg_src2_));

    std::cout << "after: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SUB::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": sub x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", x" << instr.reg_src2_ << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    std::cout << "x" << instr.reg_src2_ << " = " << hart->get_reg(instr.reg_src2_) << std::endl;

    std::cout << "before: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) - hart->get_reg(instr.reg_src2_));

    std::cout << "after: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;
    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SLL::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": sll x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", x" << instr.reg_src2_ << std::endl;
    
    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;
    std::cout << "x" << instr.reg_src2_ << " = " << hart->get_reg(instr.reg_src2_) << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) << hart->get_reg(instr.reg_src2_));

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after:  x" << instr.reg_dest_  << " = " << rd_after << std::endl;

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SLT::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": slt x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", x" << instr.reg_src2_ << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) << std::endl;
    std::cout << "x" << instr.reg_src2_ << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_)) << std::endl;
    std::cout << "before: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    if (static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) < static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)))
        hart->set_reg(instr.reg_dest_, 1);
    else
        hart->set_reg(instr.reg_dest_, 0);

    std::cout << "after: x" << instr.reg_dest_  << " = " << static_cast<SignedRegValue>(hart->get_reg(instr.reg_dest_)) << std::endl;

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SLTU::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": sltu x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", x" << instr.reg_src2_ << std::endl;
    std::cout << "x" << instr.reg_src1_ << " = " << hart->get_reg(instr.reg_src1_) << std::endl;
    std::cout << "x" << instr.reg_src2_ << " = " << hart->get_reg(instr.reg_src2_) << std::endl;
    std::cout << "before: x" << instr.reg_dest_  << " = " << hart->get_reg(instr.reg_dest_) << std::endl;

    if (hart->get_reg(instr.reg_src1_) < hart->get_reg(instr.reg_src1_))
        hart->set_reg(instr.reg_dest_, 1);
    else
        hart->set_reg(instr.reg_dest_, 0);

    std::cout << "after: x" << instr.reg_dest_  << " = " << hart->get_reg(instr.reg_dest_) << std::endl;

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_XOR::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": xor x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", x" << instr.reg_src2_ << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs2(hart->get_reg(instr.reg_src2_));
    std::cout << "x" << instr.reg_src2_ << " = " << rs2 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) ^ hart->get_reg(instr.reg_src2_));

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after: x" << instr.reg_dest_  << " = " << rd_after << std::endl;

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SRL::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": srl x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", x" << instr.reg_src2_ << std::endl;
    
    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;
    std::cout << "x" << instr.reg_src2_ << " = " << hart->get_reg(instr.reg_src2_) << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) >> hart->get_reg(instr.reg_src2_));

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after:  x" << instr.reg_dest_  << " = " << rd_after << std::endl;

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_SRA::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": sra x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", x" << instr.reg_src2_ << std::endl;
    
    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;
    std::cout << "x" << instr.reg_src2_ << " = " << hart->get_reg(instr.reg_src2_) << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    SignedRegValue res = static_cast<SignedRegValue>(hart->get_reg(instr.reg_src1_)) >> static_cast<SignedRegValue>(hart->get_reg(instr.reg_src2_));
    hart->set_reg(instr.reg_dest_, res);

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after:  x" << instr.reg_dest_  << " = " << rd_after << std::endl;

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_OR::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": or x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", x" << instr.reg_src2_ << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs2(hart->get_reg(instr.reg_src2_));
    std::cout << "x" << instr.reg_src2_ << " = " << rs2 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) | hart->get_reg(instr.reg_src2_));

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after: x" << instr.reg_dest_  << " = " << rd_after << std::endl;

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_AND::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << hart->get_pc() << ": and x" << instr.reg_dest_ <<
        ", x" << instr.reg_src1_ << ", x" << instr.reg_src2_ << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs1(hart->get_reg(instr.reg_src1_));
    std::cout << "x" << instr.reg_src1_ << " = " << rs1 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rs2(hart->get_reg(instr.reg_src2_));
    std::cout << "x" << instr.reg_src2_ << " = " << rs2 << std::endl;

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd(hart->get_reg(instr.reg_dest_));
    std::cout << "before: x" << instr.reg_dest_  << " = " << rd << std::endl;

    hart->set_reg(instr.reg_dest_, hart->get_reg(instr.reg_src1_) & hart->get_reg(instr.reg_src2_));

    std::bitset<sizeof(RegValue) * BITS_PER_BYTE> rd_after(hart->get_reg(instr.reg_dest_));
    std::cout << "after: x" << instr.reg_dest_  << " = " << rd_after << std::endl;

    std::cout << std::endl;

    return true;
}

bool ExecutorRV32I_FENCE::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "FORBIDDEN COMMAND FENCE IS CALLED!\n";
    return false;;
}

bool ExecutorRV32I_ECALL::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "FORBIDDEN COMMAND ECALL IS CALLED!\n";
    return false;
}

bool ExecutorRV32I_EBREAK::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "FORBIDDEN COMMAND EBREAK IS CALLED!\n";
    return false;;
}
