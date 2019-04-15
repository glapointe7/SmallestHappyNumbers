#include "LargeGamma.hpp"


GammaValues LargeGamma::ToVector() const
{
    GammaValues gamma_values;
    gamma_values.reserve(3 + A.size());
    
    gamma_values.push_back(R);
    gamma_values.push_back(h);
    gamma_values.push_back(number_of_iterations);
    gamma_values.insert(gamma_values.end(), A.begin(), A.end());
    
    return gamma_values;
}