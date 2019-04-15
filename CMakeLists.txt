cmake_minimum_required(VERSION 3.3)

project(Gamma)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++-3.6")

# Use the required C++11 for all libraries and executable of this project.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# No GNU or MS extensions.
set(CMAKE_CXX_EXTENSIONS OFF)

#Include the unit test source file headers.
include_directories (UnitTests)

add_executable(${PROJECT_NAME}
    SmallGammaCalculator.cpp
    LargeGamma.cpp
    LargeGammaCalculator.cpp
    GammaCalculatorFactory.cpp
    Utils/Number.cpp
    Utils/ProgressBar.cpp
    main.cpp
)

# Specify CLang compiler flags in order to transform all warnings to errors.
target_compile_options(${PROJECT_NAME} PUBLIC -Winline -Wall -Werror -pedantic-errors)
