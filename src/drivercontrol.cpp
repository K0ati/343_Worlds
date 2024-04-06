#include "main.h"
#include "drivercontrol.hpp"
#include "devices.hpp"
#include "pros/rtos.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// . . .
// 
//  DRIVER CONTROL
//
// . . .

void set_drive_to_coast() {
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftMiddle1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    leftMiddle2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);

    rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightMiddle1.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
    rightMiddle2.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
}

void set_drive_to_hold() {
    leftFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftMiddle1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    leftMiddle2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

    rightFront.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightBack.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMiddle1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    rightMiddle2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

double left_curve_function(double x, double left_curve_scale) {
  if (left_curve_scale != 0) {
    // if (CURVE_TYPE)
    return (powf(2.718, -(left_curve_scale / 10)) + powf(2.718, (fabs(x) - 127) / 10) * (1 - powf(2.718, -(left_curve_scale / 10)))) * x;
    // else
    // return powf(2.718, ((abs(x)-127)*RIGHT_CURVE_SCALE)/100)*x;
  }
  return x;
}

void set_tank(int l_stick, int r_stick) {
    leftFront.move_voltage(l_stick * (12000.0 / 127.0));
    leftBack.move_voltage(l_stick * (12000.0 / 127.0));
    leftMiddle1.move_voltage(l_stick * (12000.0 / 127.0));
    leftMiddle2.move_voltage(l_stick * (12000.0 / 127.0));

    rightFront.move_voltage(r_stick * (12000.0 / 127.0));
    rightBack.move_voltage(r_stick * (12000.0 / 127.0));
    rightMiddle1.move_voltage(r_stick * (12000.0 / 127.0));
    rightMiddle2.move_voltage(r_stick * (12000.0 / 127.0));
}

void tank_drive(double curve) {
    // Put the joysticks through the curve function
    int l_stick = left_curve_function(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y), curve);
    int r_stick = left_curve_function(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y), curve);

    // Set robot to l_stick and r_stick, check joystick threshold, set active brake
    set_tank(l_stick, r_stick);
}

void resetPistons() {

  horzWingsOut = false;
  isClampStopperOut = false;
  isIntakeUp = false;
  isRatchetOut = true;

  horzwing1.set_value(false);
  horzwing2.set_value(false);
  intake1.set_value(false);
  intake2.set_value(false);
  clampStopper.set_value(false);
  // lift.set_value(false);
}

void toggleHorzWings() {
  horzWingsOut = !horzWingsOut;
  horzwing1.set_value(horzWingsOut);
  horzwing2.set_value(horzWingsOut);
}

void toggleRatchet() {
  isRatchetOut = !isRatchetOut;
  deploy.set_value(isRatchetOut);
}

void releaseClamp() {
  clampStopper.set_value(true);
}

void togglePTO() {
  isPtoOut = !isPtoOut;
  deploy.set_value(!isPtoOut);
}

void toggleIntake() {
  isIntakeUp = !isIntakeUp;
  intake1.set_value(isIntakeUp);
  intake2.set_value(isIntakeUp);
}