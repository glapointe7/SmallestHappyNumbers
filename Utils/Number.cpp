#include "Number.hpp"

#include <algorithm>
#include <stack>


/* Convert an integer 'value' to a string. */
String Number::ToString(BigInt value)
{
    String str;
    str.reserve(10);
    do
    {
        str.push_back(static_cast<char> ('0' + (value % 10)));
    }
    while (value /= 10);
    std::reverse(str.begin(), str.end());

    return str;
}

BigInt Number::SumSquareOfDigits(const BigIntVector &digits)
{  
    BigInt sum = 0;
    const BigInt digits_length = digits.size();
    
    for(BigInt i = 0; i < digits_length; ++i)
    {
        sum += digits[i] * digits[i];
    }

    return sum;
}

String Number::ReverseDigits(BigInt x, const BigInt base)
{
    std::stack<BigInt> numbers;
    while(x > 0)
    {
        numbers.push(x % base);
        x /= base;
    }
    
    std::string seperated_digits = "";
    seperated_digits.reserve(11);
    while(!numbers.empty())
    {
        seperated_digits += ToString(numbers.top());
        seperated_digits += "-";
        numbers.pop();
    }
    seperated_digits.pop_back();
    
    return seperated_digits;
}

bool Number::IsPerfectSquare(const BigInt x)
{
    const BigInt square_root_x = static_cast<BigInt>(round(sqrt(x)));

    return square_root_x * square_root_x == x;
}

double Number::Percentage(const BigInt min, const BigInt current, const BigInt max)
{
    return (current - min) * 100.0 / (max - min);
}