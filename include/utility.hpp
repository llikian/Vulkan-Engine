/***************************************************************************************************
 * @file  utility.hpp
 * @brief Declaration of utility functions
 **************************************************************************************************/

#pragma once

#include <bitset>

template <typename Type>
std::bitset<8 * sizeof(Type)> to_bitset(Type value) {
    union {
        int64_t b;
        Type v;
    } as_byte;

    as_byte.v = value;

    return std::bitset<8 * sizeof(Type)>(as_byte.b);
}
