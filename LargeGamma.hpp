#ifndef LARGEGAMMA_HPP
#define	LARGEGAMMA_HPP

#include "Utils/Number.hpp"

#include <vector>


using DigitsVector = std::vector<BigInt>;
using GammaValues = std::vector<BigInt>;


class LargeGamma
{
public:        
    LargeGamma(const BigInt R, const BigInt base)
        : base(base), R(R), h(0), A({}), number_of_iterations(0) { }
        
    LargeGamma(const BigInt base, const BigInt R, const BigInt h, const DigitsVector &A, const BigInt number_of_iterations)
        : base(base), R(R), h(h), A(A), number_of_iterations(number_of_iterations) { }
    
    virtual ~LargeGamma() { }
    
    /* GETTERS */
    inline DigitsVector GetA() const { return A; }
    inline BigInt GetH() const { return h; }
    inline BigInt GetR() const { return R; }
    inline BigInt GetNumberOfIterations() const { return number_of_iterations; }
    
    /* Convert a LargeGamma to a vector of BigInt. */
    GammaValues ToVector() const;
    
protected:    
    const BigInt base;
    const BigInt R;
    const BigInt h;
    const DigitsVector A;
    const BigInt number_of_iterations;
};

#endif