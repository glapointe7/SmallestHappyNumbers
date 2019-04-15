#ifndef LARGEGAMMACALCULATOR_HPP
#define	LARGEGAMMACALCULATOR_HPP

#include "LargeGamma.hpp"
#include "GammaCalculator.hpp"

#include <vector>
#include <fstream>


using GammaValuesVector = std::vector<GammaValues>;
using GammaVector = std::vector<LargeGamma>;

        
class LargeGammaCalculator : public GammaCalculator
{
public:
    explicit LargeGammaCalculator(const BigInt base)
        : GammaCalculator(base) { gamma_list.reserve((base - 1) * (base - 1)); }
        
    ~LargeGammaCalculator() { }
    
    GammaVector GetGammaList() const { return gamma_list; }
    GammaValuesVector ConvertGammaListToVector() const;
    
    void Calculate() override;
    void SaveResultsToFile(std::ofstream &output) const override;
    
protected:
    GammaVector gamma_list;
    
    void CalculateWithUnknownHeight(const BigInt R);
    
    static bool LessThan(const DigitsVector &Aj, const DigitsVector &A);
    static BigInt Increment(DigitsVector &A, BigInt &i);
    static void FillWith(DigitsVector &A, const BigInt from, const BigInt digit);
    
    // Perform A_j / B^j.
    static DigitsVector DivideByBaseRaiseTo(DigitsVector Aj, const BigInt &exponent);
    DigitsVector MinimizeA(const BigInt &R) const;
};

#endif