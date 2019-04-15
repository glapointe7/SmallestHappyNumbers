
#ifndef TEST_HPP
#define	TEST_HPP

#include "../Utils/Style.hpp"
#include "TestContainer.hpp"

#include <iostream>
#include <string>
#include <vector>

using String = std::string;
using StringTest = String;

using BigInt = uint64_t;
using IntegerVector = std::vector<BigInt>;
using SequenceVector = std::vector<std::vector<BigInt> >;

namespace UnitTests
{    
// Macro to be able to automatically run unit tests easily.
#define TEST(ClassName, Parent) \
    class ClassName : public Parent \
    { \
    public: \
        ClassName() { setName(#ClassName); } \
        void run() override; \
    }; \
    class Add##ClassName \
    { \
    public: \
        Add##ClassName() { TestContainer::getInstance().append(new ClassName()); } \
    }; \
    static Add##ClassName AddThis##ClassName; \
    void ClassName::run()

    
    // Parent class for all unit tests.
    class Test  
    {
    public:
        virtual ~Test() {}
        
        virtual void setUp() = 0;
        virtual void run() = 0;
        virtual void tearDown() = 0;
        
        /* Print the result for one test if passed or failed with the expected result. */
        void printResult() const
        {
            if(has_passed)
            {
                const Style::ForegroundColor foreground_color_passed = Style::ForegroundColor::GREEN;
                std::cout << foreground_color_passed << "\n[PASSED] ";
                std::cout << Style::ResetToDefault() << name;
            }
            else
            {
                const Style::ForegroundColor foreground_color_failed = Style::ForegroundColor::YELLOW;
                std::cout << foreground_color_failed << "\n[FAILED] ";
                std::cout << Style::ResetToDefault() << name << " \n   Input value: ";
                for(const auto value : input_value)
                {
                    std::cout << foreground_color_failed << value << " ";
                }
                
                std::cout << Style::ResetToDefault() << "\nExpected value: ";
                for(const auto value : expected_value)
                {
                    std::cout << value << " ";
                }
            }
        }
                
        bool hasPassed() const { return has_passed; }
                
    protected:
        void setName(const String &name) { this->name = name; } 
        
        void compare(const IntegerVector &expected_value, const IntegerVector &input_value)
        {
            if(expected_value == input_value)
            {
                has_passed = true;
            }
            else
            {
                this->expected_value = expected_value;
                this->input_value = input_value;
                has_passed = false;
            }
        }
        
        void compare(const SequenceVector &expected_value, const SequenceVector &input_value)
        {
            const BigInt expected_value_size = expected_value.size();
            if(expected_value_size != input_value.size())
            {
                for(const auto &values : expected_value)
                {
                    this->expected_value.insert(this->expected_value.end(), values.begin(), values.end());
                }
                
                for(const auto &values : input_value)
                {
                    this->input_value.insert(this->input_value.end(), values.begin(), values.end());
                }
                
                return;
            }
            
            for(BigInt i = 0; i < expected_value_size; ++i)
            {
                if(expected_value[i] != input_value[i])
                {
                    this->expected_value = expected_value[i];
                    this->input_value = input_value[i];
                    
                    return;
                }
            }
            has_passed = true;
        }
               
    private:
        IntegerVector expected_value;
        IntegerVector input_value;
        bool has_passed = false;
        String name;
    };
}

#endif