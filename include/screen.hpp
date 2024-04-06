// screen.hpp
#pragma once

#include <string>

// Define the AutonFunction struct
struct AutonFunction {
    const char* name;
    void (*function)();
};

// Declare the autonFunctions array as extern so it can be defined in another file
extern AutonFunction autonFunctions[];

extern std::string calibrationGifs[];
extern int calibrationGifsSize;

extern std::string matchGifs[];
extern int matchGifsSize;

// Declare other functions
void calibrationScreen();
void particlesjs();
void calibrationScreenInit();
void autonSelectorScreenInit(AutonFunction autonFunctions[], size_t autonCount, lv_color_t color_scheme);
void runSelectedAuton(AutonFunction autonFunctions[], size_t autonCount);
void doNothing();
