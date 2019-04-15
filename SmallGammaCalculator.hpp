#ifndef SMALLGAMMACALCULATOR_HPP
#define	SMALLGAMMACALCULATOR_HPP

#include "GammaCalculator.hpp"
#include "Utils/Number.hpp"
#include <fstream>
#include <vector>
#include <map>

using HeightValueMap = std::map<BigInt, BigInt>;
using SmallGammaVector = std::vector<BigInt>;


class SmallGammaCalculator : public GammaCalculator
{
public:
    SmallGammaCalculator(const BigInt base, const BigInt max_value, const BigInt fixed_point)
        : GammaCalculator(base), max_value(max_value), fixed_point(fixed_point) { }
        
    ~SmallGammaCalculator() { gamma_list.clear(); }
    
    void Calculate() override;
    void SaveResultsToFile(std::ofstream &output) const override;
    
    SmallGammaVector ConvertGammaListToVector() const;
    
protected:    
    HeightValueMap gamma_list;
    const BigInt max_value;
    const BigInt fixed_point;
    
    BigInt H(BigInt x) const;
    BigInt CalculateHeight(const BigInt value) const;
};

#endif