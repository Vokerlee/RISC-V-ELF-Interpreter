#ifndef CONFIG_H_
#define CONFIG_H_

#include <cstring>
#include <cstdint>

namespace risc
{
    using PhysAddr = uint32_t;
    using VirtAddr = uint32_t;

    using RegValue   = uint32_t;
    using InstrValue = uint32_t;

    constexpr size_t kPhysMemSize = 0x1000;
    constexpr size_t kInstrSize   = sizeof(InstrValue);

    enum RegId
    {
        REG_X0,  REG_X1,
        REG_X2,  REG_X3,
        REG_X4,  REG_X5,
        REG_X6,  REG_X7,
        REG_X8,  REG_X9,
        REG_X10, REG_11,
        REG_X12, REG_13,
        REG_X14, REG_15,
        REG_X16, REG_17,
        REG_X18, REG_19,
        REG_X20, REG_21,
        REG_X22, REG_23,
        REG_X24, REG_25,
        REG_X26, REG_27,
        REG_X28, REG_29,
        REG_X30, REG_31,

        RegIdZero = REG_X0,
        RegFileGprSize = 0x20,
    };
}


#endif // !CONFIG_H_