#pragma once

#include "main.h"
#include "lemlib/api.hpp"

extern pros::Controller master;

extern pros::Motor intake;

extern pros::Motor rightFront;
extern pros::Motor rightBack;
extern pros::Motor rightMiddle1;
extern pros::Motor rightMiddle2;

extern pros::Motor leftFront;
extern pros::Motor leftBack;
extern pros::Motor leftMiddle1;
extern pros::Motor leftMiddle2;

extern pros::ADIDigitalOut horzwing1;
extern pros::ADIDigitalOut horzwing2;
extern pros::ADIDigitalOut intake1;
extern pros::ADIDigitalOut intake2;
extern pros::ADIDigitalOut deploy;
extern pros::ADIDigitalOut clampStopper;
extern pros::ADIDigitalOut pto;
// extern pros::ADIDigitalIn limitswitch;

extern bool horzWingsOut;
extern bool isClampStopperOut;
extern bool isPtoOut;
extern bool isIntakeUp;
extern bool isRatchetOut;

extern lemlib::Chassis chassis;

extern Drive EzTempChassis;

void checkMotorsAndReturnTemperature();
void checkPTODeploy();

void calibrateBothChassis(bool isLemLib = false);
void ezTempChassisInits();

// Change Pneumatic, Motor Names, Motor Temp name
