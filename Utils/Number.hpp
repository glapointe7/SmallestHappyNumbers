#ifndef NUMBER_HPP
#define	NUMBER_HPP

#include <string>
#include <stdint.h>
#include <assert.h>
#include <vector>

using String = std::string;
using BigInt = uint64_t;
using BigIntVector = std::vector<BigInt>;


namespace Number
{    
    String ToString(BigInt value);
    
    BigInt SumSquareOfDigits(const BigIntVector &digits);
    
    String ReverseDigits(BigInt x, const BigInt base);
    
    bool IsPerfectSquare(const BigInt x);
    
    double Percentage(const BigInt min, const BigInt current, const BigInt max);
}

#endif