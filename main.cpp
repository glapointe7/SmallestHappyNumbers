#include "GammaCalculatorFactory.hpp"
#include "Utils/ProgressBar.hpp"

#include <iostream>
#include <memory>
#include <chrono>
#include <iomanip>

#include "UnitTests/TestContainer.hpp"
#include "UnitTests/LargeGammaTest.hpp"
#include "UnitTests/SmallGammaTest.hpp"


using namespace std::chrono;
using Time = high_resolution_clock;


void RunAndSaveCalculation(const GammaCalculatorType gamma_calculator_type, const std::string &filename, 
        const BigInt min_base, const BigInt max_base, const BigInt max_value, const BigInt fixed_point)
{
    const std::string dataset_path = "../../Dataset/";
    std::ofstream output(dataset_path + filename + ".csv", std::ios_base::app);
    const auto start_time = Time::now();
    
    //const ProgressBar progress_bar(Style::BackgroundColor::BLUE);
    for(BigInt B = min_base; B <= max_base; ++B)
    {
        //const double percentage = Number::Percentage(min_base, B, max_base);
        std::cout << "\033[2K\r" << "Base: " << B << " / " << max_base;
        //progress_bar.Show(percentage);
        
        std::shared_ptr<GammaCalculator> gamma_calculator = GammaCalculatorFactory::CreateGammaCalculator(gamma_calculator_type, B, max_value, fixed_point);
        gamma_calculator->Calculate();
        gamma_calculator->SaveResultsToFile(output);

        rewind(stdout);
    }
    
    output.close();
    const auto end_time = Time::now();
    const double elapsed_time = duration<double, std::milli>(end_time - start_time).count() / 60000;
    std::cout << "\nRun time = " << elapsed_time << " minutes\n\n";
}

void RunAndSaveBenchmark(const GammaCalculatorType gamma_calculator_type, const BigInt repeatitions, 
        const std::string &filename, const BigInt min_base, const BigInt max_base, const BigInt max_value, const BigInt fixed_point)
{
    const std::string dataset_path = "../../Dataset/";    
    std::ofstream output(dataset_path + filename + ".csv");
    
    for(BigInt B = min_base; B <= max_base; ++B)
    {
        const double percentage = Number::Percentage(min_base, B, max_base);
        std::cout << "\033[2K\r" << "Base = " << B << "  -  " << std::setprecision(3) << percentage << " %";
        
        std::shared_ptr<GammaCalculator> gamma_calculator = GammaCalculatorFactory::CreateGammaCalculator(gamma_calculator_type, B, max_value, fixed_point);
        
        double mean_time = 0.0;
        for(BigInt i = 1; i <= repeatitions; ++i)
        {
            const auto start_time = Time::now();

            gamma_calculator->Calculate();

            const auto end_time = Time::now();
            mean_time += duration<double, std::milli>(end_time - start_time).count();
        }
        mean_time /= repeatitions;
        
        output << B << ";";
        output << mean_time << "\n";

        rewind(stdout);
    }
    
    output.close();
}


int main(int argc, char** argv)
{    
    if(argc > 4 || argc == 2)
    {
        std::cerr << "Number of parameters mismatch. The correct syntax is: ./GammaHappyNumber <base min> <base max> [Max number to test] where [Max number to test] is optional.\n";
        return 0;
    }
    
    // Run the unit tests.
    if(argc == 1)
    {
        UnitTests::TestContainer::runAllTests();
        
        return 0;
    }
    
    const BigInt min_base = std::stoull(String(argv[1]));
    const BigInt max_base = std::stoull(String(argv[2]));
    if(min_base < 3 || max_base < 3)
    {
        std::cerr << "The numerical base must be greater or equal than 3.\n";
        return 0;
    }
    
    if(argc == 3)
    {
        RunAndSaveCalculation(GammaCalculatorType::LARGE_GAMMA, "LargeGamma", min_base, max_base, 0, 1);
        
        return 0;
    }
    
    if(argc == 4)
    {
        const BigInt max_value = std::stoull(String(argv[3]));
        
        RunAndSaveCalculation(GammaCalculatorType::SMALL_GAMMA, "SmallGamma", min_base, max_base, max_value, 1);
    }
    
    return 0;
}