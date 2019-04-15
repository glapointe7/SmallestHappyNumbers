#include "ProgressBar.hpp"

#include <iostream>
#include <iomanip>
#include <string>


void ProgressBar::Show(const double percentage) const
{
    std::cout << "    [" 
              << background_color << std::string(static_cast<uint8_t>(percentage), ' ') << Style::ResetToDefault() 
              << std::setw (100 - static_cast<uint8_t>(percentage)) << "]";
    std::cout << "  [" << Style::ForegroundColor::LIGHT_CYAN << std::setprecision(3) << percentage << "%" << Style::ResetToDefault() << "]";
}