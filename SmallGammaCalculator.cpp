#include "SmallGammaCalculator.hpp"

#include <limits>
#include <algorithm>


BigInt SmallGammaCalculator::H(BigInt x) const
{
    BigInt new_number = 0;
    while (x > 0)
    {
        const BigInt digit = x % base;
        new_number += digit * digit;
        x /= base;
    }

    return new_number;
}

BigInt SmallGammaCalculator::CalculateHeight(const BigInt value) const
{
    BigInt x = value;
    SmallGammaVector evaluated_values;
    evaluated_values.reserve(2 * base);
    evaluated_values.push_back(x);

    BigInt height = 0;
    x = H(x);
    while(std::find(evaluated_values.begin(), evaluated_values.end(), x) == evaluated_values.end())
    {
        height++;
        evaluated_values.push_back(x);
        x = H(x);
    }
    
    return (x == fixed_point) ? height : std::numeric_limits<BigInt>::max();
}

void SmallGammaCalculator::Calculate()
{   
    for(BigInt x = 1; x <= max_value; ++x)
    {
        const BigInt height = CalculateHeight(x);
        if(height < std::numeric_limits<BigInt>::max())
        {
            if(gamma_list.find(height) == gamma_list.end())
            {
                gamma_list[height] = x;
            }
        }
    }
}

void SmallGammaCalculator::SaveResultsToFile(std::ofstream &output) const
{
    for(const std::pair<BigInt, BigInt> &gamma : gamma_list)
    {
        output << base << ",";
        output << gamma.first << ",";
        output << Number::ReverseDigits(gamma.second, base) << "\n";
    }
}

SmallGammaVector SmallGammaCalculator::ConvertGammaListToVector() const
{
    SmallGammaVector gamma_vector;
    gamma_vector.reserve(gamma_list.size() * 2);
    
    for(const std::pair<BigInt, BigInt> &gamma : gamma_list)
    {
        gamma_vector.push_back(gamma.first);
        gamma_vector.push_back(gamma.second);
    }
    
    return gamma_vector;
}