# Summary
This is the implementation in C++11 of the algorithms about the smallest happy numbers of unknown height and their test cases for decimal and octal bases.

# Compilation
This code has been compiled with CLang version 3.6 using `cmake` or with Netbeans version 8.0.2.

# Compilation using CMake
Make sure to install `cmake` 3.3 in order to built the executable. Here is the procedure to execute the code in the terminal with cmake:

1. `mkdir Build` - Create the directory 'Build'
2. `cd Build` - Enter the 'Build' directory
3. `cmake ..` - Build and generate the target compiler from the `CMakeList.txt` file
4. `make Gamma` - Compile the source code and create the executable `Gamma` accordingly
5. `./Gamma <base_min> <base_max>` - Write gamma in base B between `base_min` and `base_max` inclusively in the CSV file `LargeGamma.csv`