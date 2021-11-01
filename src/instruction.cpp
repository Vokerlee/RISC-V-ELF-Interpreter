#include "config.h"
#include "utils.hpp"
#include "instruction.h"

using namespace risc;

Instruction::Instruction(InstrValue instr)
{
    decode(instr);
}

Instruction::~Instruction()
{
   // if (is_corrupted() == false)
     //   delete executor_;
}


bool Instruction::is_corrupted() const
{
    if (instr_class_ == RV32I_ERROR)
        return true;
    else 
        return false;
}

bool Instruction::decode(InstrValue instr)
{
    switch (instr & 0b1111111) // OPCODE
    {
        case 0:
            return false;
        case 0b0110111: // LUI
        {
            instr_class_ = RV32I_LUI;
            executor_    = new ExecutorRV32I_LUI;
            reg_dest_    = static_cast<RegId>(get_bits<11, 7>(instr) >> 7);
            immediate_   = get_bits<31, 12>(instr);  

            break;
        }
        case 0b0010111: // AUIPC
        {
            instr_class_ = RV32I_AUIPC;
            executor_    = new ExecutorRV32I_AUIPC;   
            reg_dest_    = static_cast<RegId>(get_bits<11, 7>(instr) >> 7);
            immediate_   = get_bits<31, 12>(instr);

            break;
        }
        case 0b1101111: // JAL
        {
            instr_class_ = RV32I_JAL;
            executor_    = new ExecutorRV32I_JAL;
            reg_dest_    = static_cast<RegId>(get_bits<11, 7>(instr) >> 7);
            
            RegValue init_imm = get_bits<31, 12>(instr);

            immediate_ = (static_cast<SignedRegValue>(get_bits<31, 31>(instr)) >> 11) + (get_bits<30, 21>(instr) >> 20) + 
                            (get_bits<20, 20>(instr) >> 9)  + (get_bits<19, 12>(instr));  
            break;
        }
        case 0b1100111: // JALR 
        {
            RegValue funct3 = get_bits<14, 12>(instr) >> 12;
            if (funct3 == 0b000)
            {
                instr_class_ = RV32I_JALR;
                executor_ = new ExecutorRV32I_JALR;
                reg_dest_ = static_cast<RegId>(get_bits<11, 7>(instr)  >> 7);
                reg_src1_ = static_cast<RegId>(get_bits<19, 15>(instr) >> 15);

                immediate_ = static_cast<SignedRegValue>(get_bits<31, 20>(instr)) >> 20;
            }
            else
                return false;

            break;
        }
        case 0b1100011: // BEQ / BNE / BLT / BGE / BLTU / BGEU
        {
            RegValue funct3 = get_bits<14, 12>(instr) >> 12;

            switch(funct3)
            {
                case 0b000:
                    instr_class_ = RV32I_BEQ;
                    executor_    = new ExecutorRV32I_BEQ;
                    break;
                case 0b001:
                    instr_class_ = RV32I_BNE;
                    executor_    = new ExecutorRV32I_BNE;
                    break;
                case 0b100:
                    instr_class_ = RV32I_BLT;
                    executor_    = new ExecutorRV32I_BLT;
                    break;
                case 0b101:
                    instr_class_ = RV32I_BGE;
                    executor_    = new ExecutorRV32I_BGE;
                    break;
                case 0b110:
                    instr_class_ = RV32I_BLTU;
                    executor_    = new ExecutorRV32I_BLTU;
                    break;
                case 0b111:
                    instr_class_ = RV32I_BGEU;
                    executor_    = new ExecutorRV32I_BGEU;
                    break;
                default:
                    return false;
            }

            reg_src1_ = static_cast<RegId>(get_bits<19, 15>(instr) >> 15);
            reg_src2_ = static_cast<RegId>(get_bits<24, 20>(instr) >> 20);  

            immediate_ = (static_cast<SignedRegValue>(get_bits<31, 31>(instr)) >> 19) + (get_bits<30, 25>(instr) >> 20) +
                            (get_bits<11, 8>(instr)  >> 7)  + (get_bits<7, 7>(instr)   << 4);
            break;  
        }
        case 0b0000011: // LB / LH / LW / LBU / LHU
        {
            RegValue funct3 = get_bits<14, 12>(instr) >> 12;

            switch(funct3)
            {
                case 0b000:
                    instr_class_ = RV32I_LB;
                    executor_    = new ExecutorRV32I_LB;
                    break;
                case 0b001:
                    instr_class_ = RV32I_LH;
                    executor_    = new ExecutorRV32I_LH;
                    break;
                case 0b010:
                    instr_class_ = RV32I_LW;
                    executor_    = new ExecutorRV32I_LW;
                    break;
                case 0b100:
                    instr_class_ = RV32I_LBU;
                    executor_    = new ExecutorRV32I_LBU;
                    break;
                case 0b101:
                    instr_class_ = RV32I_LHU;
                    executor_    = new ExecutorRV32I_LHU;
                    break;
                default:
                    return false;
            }

            reg_src1_ = static_cast<RegId>(get_bits<19, 15>(instr) >> 15);
            immediate_ = static_cast<SignedRegValue>(get_bits<31, 20>(instr)) >> 20;

            break;
        }
        case 0b0100011: // SB / SH / SW
        {
            RegValue funct3 = get_bits<14, 12>(instr) >> 12;

            switch(funct3)
            {
                case 0b000:
                    instr_class_ = RV32I_SB;
                    executor_    = new ExecutorRV32I_SB;
                    break;
                case 0b001:
                    instr_class_ = RV32I_SH;
                    executor_    = new ExecutorRV32I_SH;
                    break;
                case 0b010:
                    instr_class_ = RV32I_SW;
                    executor_    = new ExecutorRV32I_SW;
                    break;
                default:
                    return false;
            }
            
            reg_src1_ = static_cast<RegId>(get_bits<19, 15>(instr) >> 15);
            reg_src2_ = static_cast<RegId>(get_bits<24, 20>(instr) >> 20);
            immediate_ = (static_cast<SignedRegValue>(get_bits<31, 25>(instr)) >> 20) + (get_bits<11, 7>(instr) >> 7);
            
            break;
        }
        case 0b0010011: // ADDI / SLTI / SLTIU / XORI / ORI / ANDI / SLLI / SRLI / SRAI
        {
            RegValue funct3 = get_bits<14, 12>(instr) >> 12;
            RegValue funct7 = get_bits<31, 25>(instr) >> 25;

            switch(funct3)
            {
                case 0b000:
                    instr_class_ = RV32I_ADDI;
                    executor_ = new ExecutorRV32I_ADDI;
                    goto i_type;
                case 0b001:
                    if (funct7 == 0b0000000)
                    {   instr_class_ = RV32I_SLLI;
                        executor_    = new ExecutorRV32I_SLLI;
                    }
                    else
                        return false;
                    goto r_type;
                case 0b010:
                    instr_class_ = RV32I_SLTI;
                    executor_    = new ExecutorRV32I_SLTI;
                    goto i_type;
                case 0b011:
                    instr_class_ = RV32I_SLTIU;
                    executor_    = new ExecutorRV32I_SLTIU;
                    goto i_type;
                case 0b100:
                    instr_class_ = RV32I_XORI;
                    executor_    = new ExecutorRV32I_XORI;
                    goto i_type;
                case 0b101:
                    if (funct7 == 0b0000000)
                    {
                        instr_class_ = RV32I_SRLI;
                        executor_    = new ExecutorRV32I_SRLI;
                    }
                    else if (funct7 == 0b0100000)
                    {
                        instr_class_ = RV32I_SRAI;
                        executor_    = new ExecutorRV32I_SRAI;
                    }
                    goto r_type;
                case 0b110:
                    instr_class_ = RV32I_ORI;
                    executor_    = new ExecutorRV32I_ORI;
                    goto i_type;
                case 0b111:
                    instr_class_ = RV32I_ANDI;
                    executor_    = new ExecutorRV32I_ANDI;
                    goto i_type;
        i_type:
                    immediate_ = static_cast<SignedRegValue>(get_bits<31, 20>(instr)) >> 20;
                    break;
        r_type:
                    immediate_ = static_cast<SignedRegValue>(get_bits<24, 20>(instr)) >> 20;
                    break;
                default:
                    return false;
            }

            reg_src1_ = static_cast<RegId>(get_bits<19, 15>(instr) >> 15);
            reg_dest_ = static_cast<RegId>(get_bits<11, 7>(instr) >> 7);

            break;
        }
        case 0b0110011: // ADD / SUB / SLL / SLT / SLTU / XOR / SRL / SRA / OR / AND
        {
            RegValue funct3 = get_bits<14, 12>(instr) >> 12;
            RegValue funct7 = get_bits<31, 25>(instr) >> 25;

            if (funct3 == 0b000 && funct7 == 0b0000000)
            {
                instr_class_ = RV32I_ADD;
                executor_    = new ExecutorRV32I_ADD;
            }
            else if (funct3 == 0b000 && funct7 == 0b0100000)
            {
                instr_class_ = RV32I_SUB;
                executor_    = new ExecutorRV32I_SUB;
            }
            
            else if (funct3 == 0b001 && funct7 == 0b0000000)
            {
                instr_class_ = RV32I_SLL;
                executor_    = new ExecutorRV32I_SLL;
            }
            else if (funct3 == 0b010 && funct7 == 0b0000000)
            {
                instr_class_ = RV32I_SLT;
                executor_    = new ExecutorRV32I_SLT;
            }
            else if (funct3 == 0b011 && funct7 == 0b0000000)
            {
                instr_class_ = RV32I_SLTU;
                executor_    = new ExecutorRV32I_SLTU;
            }
            else if (funct3 == 0b100 && funct7 == 0b0000000)
            {
                instr_class_ = RV32I_XOR;
                executor_    = new ExecutorRV32I_XOR;
            }
            else if (funct3 == 0b101 && funct7 == 0b0000000)
            {
                instr_class_ = RV32I_SRL;
                executor_    = new ExecutorRV32I_SRL;
            }
            else if (funct3 == 0b101 && funct7 == 0b0100000)
            {
                instr_class_ = RV32I_SRA;
                executor_    = new ExecutorRV32I_SRA;
            }
            else if (funct3 == 0b110 && funct7 == 0b0000000)
            {
                instr_class_ = RV32I_OR;
                executor_    = new ExecutorRV32I_OR;
            }
            else if (funct3 == 0b111 && funct7 == 0b0000000)
            {
                instr_class_ = RV32I_AND;
                executor_    = new ExecutorRV32I_AND;
            }
            else
                return false;

            reg_dest_ = static_cast<RegId>(get_bits<11, 7>(instr) >> 7);
            reg_src1_ = static_cast<RegId>(get_bits<19, 15>(instr) >> 15);
            reg_src2_ = static_cast<RegId>(get_bits<24, 20>(instr) >> 20);

            break;
        }
        case 0b0001111: // FENCE
        {
            RegValue funct3 = get_bits<14, 12>(instr) >> 12;

            if (funct3 == 0b000)
            {
                instr_class_ = RV32I_FENCE;
                executor_    = new ExecutorRV32I_FENCE;

                reg_dest_ = static_cast<RegId>(get_bits<11, 7>(instr) >> 7);
                reg_src1_ = static_cast<RegId>(get_bits<19, 15>(instr) >> 15);
                
                immediate_ = immediate_ = get_bits<31, 20>(instr) >> 20;
            }
            else 
                return false;

            break;
        }
        case 0b1110011: // ECALL / EBREAK
        {
            RegValue id         = get_bits<31, 20>(instr) >> 20;
            RegValue other_bits = get_bits<19, 7> (instr) >> 7;

            if (id == 0 && other_bits == 0)
            {
                instr_class_ = RV32I_ECALL;
                executor_    = new ExecutorRV32I_ECALL;
            }
            else if (id == 1 && other_bits == 0)
            {
                instr_class_ = RV32I_EBREAK;
                executor_    = new ExecutorRV32I_EBREAK;
            }
            else
                return false;
        }
        default:
            return false;
    }

    return true;
}
