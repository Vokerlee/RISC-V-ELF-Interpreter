#ifndef UTILS_H_
#define UTILS_H_

#include <iostream>
#include "config.h"

namespace risc
{
    template<uint8_t high, uint8_t low, class T = RegId>
    T get_bits(T value)
    {
        T mask = ((1UL << (high - low + 1)) - 1) << low;
        return (value & mask);
    }
}

#endif // !UTILS_H_