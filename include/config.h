#ifndef CONFIG_H_
#define CONFIG_H_

#include <cstring>
#include <cstdint>

namespace risc
{
    using PhysPageOffset = uint32_t;
    using VirtAddr       = uint32_t;

    using RegValue       = uint32_t;
    using SignedRegValue = int32_t;
    using InstrValue     = uint32_t;

    using Byte           = uint8_t;
    using SignedByte     = int8_t;
    using HWord          = uint16_t;
    using SignedHWord    = int16_t;

    constexpr size_t kNOffsetBits = 16;

    constexpr size_t kPhysPageSize = 1 << kNOffsetBits;
    constexpr size_t kVirtMemSize  = 0x100000000;
    constexpr size_t kNVirtPages   = kVirtMemSize / kPhysPageSize;

    constexpr VirtAddr kOffsetMask = (1 << kNOffsetBits) - 1;

    constexpr size_t kInstrSize = sizeof(InstrValue);

    constexpr size_t kDefaultStackAddress = 0x30000000;

    enum DebugRegime
    {
        DBG_OFF,
        DBG_ON
    };

    enum RegId
    {
        REG_X0  = 0,  REG_X1  = 1,
        REG_X2  = 2,  REG_X3  = 3,
        REG_X4  = 4,  REG_X5  = 5,
        REG_X6  = 6,  REG_X7  = 7,
        REG_X8  = 8,  REG_X9  = 9,
        REG_X10 = 10, REG_X11 = 11,
        REG_X12 = 12, REG_X13 = 13,
        REG_X14 = 14, REG_X15 = 15,
        REG_X16 = 16, REG_X17 = 17,
        REG_X18 = 18, REG_X19 = 19,
        REG_X20 = 20, REG_X21 = 21,
        REG_X22 = 22, REG_X23 = 23,
        REG_X24 = 24, REG_X25 = 25,
        REG_X26 = 26, REG_X27 = 27,
        REG_X28 = 28, REG_X29 = 29,
        REG_X30 = 30, REG_X31 = 31,

        RegIdZero = REG_X0,
        RegFileGprSize = 0x20,
    };

    enum InstrClass // ONLY RV32I BASE INSTRUCTIONS
    {
        RV32I_LUI,
        RV32I_AUIPC,
        RV32I_JAL,
        RV32I_JALR,
        RV32I_BEQ,
        RV32I_BNE,
        RV32I_BLT,
        RV32I_BGE,
        RV32I_BLTU,
        RV32I_BGEU,
        RV32I_LB,
        RV32I_LH,
        RV32I_LW,
        RV32I_LBU,
        RV32I_LHU,
        RV32I_SB,
        RV32I_SH,
        RV32I_SW,
        RV32I_ADDI,
        RV32I_SLTI,
        RV32I_SLTIU,
        RV32I_XORI,
        RV32I_ORI,
        RV32I_ANDI,
        RV32I_SLLI,
        RV32I_SRLI,
        RV32I_SRAI,
        RV32I_ADD,
        RV32I_SUB,
        RV32I_SLL,
        RV32I_SLT,
        RV32I_SLTU,
        RV32I_XOR,
        RV32I_SRL,
        RV32I_SRA,
        RV32I_OR,
        RV32I_AND,
        RV32I_FENCE,
        RV32I_ECALL,
        RV32I_EBREAK,
        RV32I_ERROR
    };
}


#endif // !CONFIG_H_
