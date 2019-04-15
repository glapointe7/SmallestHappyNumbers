#ifndef SMALLGAMMATEST_HPP
#define	SMALLGAMMATEST_HPP

#include "Test.hpp"
#include "../SmallGammaCalculator.hpp"

namespace UnitTests
{
    class SmallGammaTest : public Test
    {
    protected:
        static constexpr BigInt MAX_VALUE = 1000000;
        static constexpr BigInt FIXED_POINT = 1;
        
        SmallGammaCalculator *gamma_list_base_4;
        SmallGammaCalculator *gamma_list_base_10;
                
        void setUp() override
        {
            gamma_list_base_4 = new SmallGammaCalculator(4, MAX_VALUE, FIXED_POINT);
            gamma_list_base_10 = new SmallGammaCalculator(10, MAX_VALUE, FIXED_POINT);
        }

        void tearDown() override
        {
            delete gamma_list_base_4;
            delete gamma_list_base_10;
        }
    };
    
    TEST(Small_Gamma_Base_4_Test, SmallGammaTest)
    {
        const SmallGammaVector expected_value = {
            0, 1,
            1, 4,
            2, 2,
            3, 5,
            4, 6,
            5, 3,
            6, 21,
            7, 63,
            8, 16383
        };
        
        gamma_list_base_4->Calculate();
        const SmallGammaVector input_value = gamma_list_base_4->ConvertGammaListToVector();
        
        compare(expected_value, input_value);
    }
    
    TEST(Small_Gamma_Base_10_Test, SmallGammaTest)
    {
        const SmallGammaVector expected_value = {
            0, 1,
            1, 10,
            2, 13,
            3, 23,
            4, 19,
            5, 7,
            6, 356,
            7, 78999
        };
        
        gamma_list_base_10->Calculate();
        const SmallGammaVector input_value = gamma_list_base_10->ConvertGammaListToVector();
        
        compare(expected_value, input_value);
    }
}

#endif