
#ifndef TESTCONTAINER_HPP
#define	TESTCONTAINER_HPP

#include "Test.hpp"

#include <chrono>

namespace UnitTests
{
    using namespace std::chrono;
    using Time = high_resolution_clock;
    
    class TestContainer
    {
    private:
        TestContainer() {}
        
        static std::vector<Test *> unit_tests_vector;
        static uint64_t total_passed_tests;
        static double total_executed_time;
        
    public:
        static TestContainer &getInstance() 
        { 
            static TestContainer instance;
            return instance; 
        }
        
        void append(Test *const CurrentTest)
        {
            unit_tests_vector.push_back(CurrentTest);
        }
        
        static void runAllTests()
        {
            for(const auto &current_test : unit_tests_vector)
            {
                const auto start_time = Time::now();
                current_test->setUp();
                current_test->run();
                current_test->tearDown();
                const auto end_time = Time::now();
                
                const double elapsed_time = duration<double, std::milli>(end_time - start_time).count();
                total_executed_time += elapsed_time;
                total_passed_tests += current_test->hasPassed();
                current_test->printResult();
                std::cout << "\nTime elapsed: " << elapsed_time << " ms\n";
            }
            
            printReport();
        }
        
        static void printReport()
        {
            const uint64_t total_tests = unit_tests_vector.size();
            std::cout << "\n Tests passed: " << total_passed_tests;
            std::cout << "\n Tests failed: " << (total_tests - total_passed_tests);
            std::cout << "\n Total tests executed: " << total_tests;
            std::cout << "\n Total time elapsed: " << total_executed_time << " ms\n";
        }
    };
    
    std::vector<Test *> TestContainer::unit_tests_vector;
    uint64_t TestContainer::total_passed_tests = 0;
    double TestContainer::total_executed_time = 0.0;
}

#endif