#ifndef GAMMACALCULATORFACTORY_HPP
#define	GAMMACALCULATORFACTORY_HPP

#include "GammaCalculator.hpp"
#include "Utils/Number.hpp"
#include <memory>


enum class GammaCalculatorType : uint8_t
{
    SMALL_GAMMA = 1,
    LARGE_GAMMA = 2
};


class GammaCalculatorFactory
{
public:
    static std::shared_ptr<GammaCalculator> CreateGammaCalculator(const GammaCalculatorType gamma_type, 
            const BigInt base, const BigInt max_value, const BigInt fixed_point);
};

#endif
