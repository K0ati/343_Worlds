#pragma once

#include "pros/rtos.hpp"
#include "lemlib/api.hpp"

// . . .
// 
//  DRIVER CONTROL
//
// . . .
void resetPistons();
void toggleHorzWings();
void toggleIntake();
void togglePTO();
void releaseClamp();
void toggleDeploy();
// void toggleLift();
bool getShiftKey();
// void drop();



void tank_drive(double curve = 6.0);
void set_drive_to_coast();
void set_drive_to_hold();