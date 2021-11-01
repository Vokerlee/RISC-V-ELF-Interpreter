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
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_AUIPC::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "AUIPC was called!\n";
    return true;
}

bool ExecutorRV32I_JAL::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_JALR::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_BEQ::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_BNE::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_BLT::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_BGE::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_BLTU::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_BGEU::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_LB::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_LH::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_LW::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_LBU::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_LHU::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_SB::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_SH::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_SW::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
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
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_ECALL::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}

bool ExecutorRV32I_EBREAK::operator()(Hart* hart, const Instruction& instr)
{
    std::cout << "LUI was called!\n";
    return true;
}
