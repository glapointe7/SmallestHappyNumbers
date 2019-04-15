#include "LargeGammaCalculator.hpp"
#include "Utils/ProgressBar.hpp"

#include <iostream>
#include <iomanip>
#include <cmath>


void LargeGammaCalculator::Calculate()
{
    const BigInt squared_base = (base - 1) * (base - 1);
    const ProgressBar progress_bar(Style::BackgroundColor::BLUE);
    
    for(BigInt R = 0; R < squared_base; ++R)
    {   
        const BigInt percentage = static_cast<uint8_t>(R * 100.0 / (squared_base - 1));
        std::cout << "\033[2K\r" << "Base = " << base << "   R = " << R << " / " << squared_base  - 1;
        progress_bar.Show(percentage);

        CalculateWithUnknownHeight(R);
        
        rewind(stdout);
    }
    std::cout << "\n\n";
}

void LargeGammaCalculator::SaveResultsToFile(std::ofstream &output) const
{
    for(const LargeGamma &gamma : gamma_list)
    {
        output << base << ",";
        output << gamma.GetR() << ",";
        output << gamma.GetH() << ",";
        output << gamma.GetNumberOfIterations() << ",";
        for(const BigInt &digit : gamma.GetA())
        {
            output << digit << "-";
        }
        output.seekp(-1, std::ios::cur);
        output << "\n";
    }
}

GammaValuesVector LargeGammaCalculator::ConvertGammaListToVector() const
{
    GammaValuesVector gamma_values_vector;
    gamma_values_vector.reserve(gamma_list.size());
    for(const LargeGamma &gamma : gamma_list)
    {
        gamma_values_vector.push_back(gamma.ToVector());
    }
    
    return gamma_values_vector;
}



void LargeGammaCalculator::FillWith(DigitsVector &A, const BigInt from, const BigInt digit)
{
    const BigInt A_length = A.size();
    for(BigInt i = from; i < A_length; ++i)
    {
        A[i] = digit;
    }
}

BigInt LargeGammaCalculator::Increment(DigitsVector &A, BigInt &i) 
{
    if (i == 0) 
    {
        FillWith(A, 0, 1);
        A.push_back(1);
    } 
    else 
    {
        const BigInt new_digit = ++A[--i];
        FillWith(A, i, new_digit);
    }
    
    return A.size() - 1;
}

DigitsVector LargeGammaCalculator::MinimizeA(const BigInt &R) const
{
    const BigInt max_digit = base - 2;
    const BigInt squared_max_digit = max_digit * max_digit;
    
    const BigInt D = R / squared_max_digit + 1;
    BigInt j = D - 1;
    if (j * squared_max_digit == R) 
    {
        return DigitsVector(j, max_digit);
    }

    BigInt i = 0;
    DigitsVector A = DigitsVector(D, 1);
    BigInt h = Number::SumSquareOfDigits(A);
    while (h != R)
    {
        if(h > R || A[j] == max_digit)
        {
            j = Increment(A, i);
        }
        else
        {
            A[j]++;
            i = j;
        }
        h = Number::SumSquareOfDigits(A);
    }
    
    return A;
}

void LargeGammaCalculator::CalculateWithUnknownHeight(const BigInt R)
{
    const BigInt square_root_R = static_cast<BigInt>(round(sqrt(R)));
    DigitsVector A;
    A.reserve(3*base/2 - 3);
    BigInt h = R;
    BigInt number_of_iterations = 0;
    if(square_root_R * square_root_R == R)
    {
        A = DigitsVector{square_root_R};
    }
    else
    {
        // First iteration: j = 0
        DigitsVector Aj_minus_one = MinimizeA(R);
        A = Aj_minus_one;
            
        const BigInt squared_base_minus_one = (base - 1) * (base - 1);
        const BigInt upper_bound = base/2 + 1;//3*base / 2 - 3;
        
        for(BigInt j = 1; j <= upper_bound; ++j)
        {
            const BigInt Rj = R + j * squared_base_minus_one;
            const DigitsVector Aj = MinimizeA(Rj);

            // A_j / B^j < A
            const DigitsVector Aj_divided_by_Bj = DivideByBaseRaiseTo(Aj, j);
            if(LessThan(Aj_divided_by_Bj, Aj_minus_one))
            {
                h = Rj;
                A = Aj;
                number_of_iterations = j;
                Aj_minus_one = Aj_divided_by_Bj;
            }
        }
    }
    
    gamma_list.push_back({base, R, h, A, number_of_iterations});
}

DigitsVector LargeGammaCalculator::DivideByBaseRaiseTo(DigitsVector Aj, const BigInt &exponent)
{
    for(BigInt i = 0; i < exponent; ++i)
    {
        Aj.pop_back();
    }
    
    return Aj;
}

bool LargeGammaCalculator::LessThan(const DigitsVector &Aj, const DigitsVector &A)
{   
    const BigInt Aj_divided_by_Bj_size = Aj.size();
    const BigInt A_size = A.size();
    
    // Case when Aj > A is the most probable.
    if(Aj_divided_by_Bj_size > A_size)
    {
        return false;
    }
    
    if(Aj_divided_by_Bj_size == A_size)
    {
        // The loop stands only if A_j_div[i] = A[i] (same digit).
        for(BigInt i = 0; i < Aj_divided_by_Bj_size; ++i)
        {
            if(Aj[i] != A[i])
            {
                return Aj[i] < A[i];
            }
        }
    }
    
    return true;
}