#include "GammaCalculatorFactory.hpp"

#include "SmallGammaCalculator.hpp"
#include "LargeGammaCalculator.hpp"


std::shared_ptr<GammaCalculator> GammaCalculatorFactory::CreateGammaCalculator(const GammaCalculatorType gamma_type, 
        const BigInt base, const BigInt max_value, const BigInt fixed_point)
{
    switch(gamma_type)
    {
        case GammaCalculatorType::SMALL_GAMMA:
            return std::shared_ptr<SmallGammaCalculator>(new SmallGammaCalculator(base, max_value, fixed_point));
            
        case GammaCalculatorType::LARGE_GAMMA:
            return std::shared_ptr<LargeGammaCalculator>(new LargeGammaCalculator(base));
            
        default:
            return nullptr;
    }
}