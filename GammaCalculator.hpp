#ifndef GAMMACALCULATOR_HPP
#define	GAMMACALCULATOR_HPP

#include "Utils/Number.hpp"
#include <fstream>


class GammaCalculator
{
public: 
    explicit GammaCalculator(const BigInt base) : base(base) { }
    virtual ~GammaCalculator() { }
    
    virtual void Calculate() = 0;  
    virtual void SaveResultsToFile(std::ofstream &output) const = 0;
    
protected:
    const BigInt base;
};

#endif