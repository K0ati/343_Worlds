#include "lemlib/api.hpp"
#include "main.h"
#include "devices.hpp"
#include "drivercontrol.hpp"

bool horzWingsOut = false;
bool isClampStopperOut = false;
bool isPtoOut = false;
bool isIntakeUp = false;
bool isRatchetOut = false;


pros::ADIDigitalOut intake1('C');
pros::ADIDigitalOut intake2('C');
pros::ADIDigitalOut pto('A');
pros::ADIDigitalOut horzwing1('D');
pros::ADIDigitalOut deploy('B');
pros::ADIDigitalOut horzwing2('D');
pros::ADIDigitalOut clampStopper('X');
// pros::ADIDigitalIn limitswitch ('E');


pros::Motor intake (-16, pros::E_MOTOR_GEARSET_18, true, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor leftFront(17, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor leftBack(18, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor leftMiddle1(19, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor leftMiddle2(20, pros::E_MOTOR_GEARSET_18, false); 

pros::Motor rightMiddle1(14, pros::E_MOTOR_GEARSET_18, true); 
pros::Motor rightFront(13, pros::E_MOTOR_GEARSET_06, true); 
pros::Motor rightBack(12, pros::E_MOTOR_GEARSET_06, false); 
pros::Motor rightMiddle2(11, pros::E_MOTOR_GEARSET_06, true); 

pros::MotorGroup left_side_motors({leftFront, leftBack, leftMiddle1, leftMiddle2});
pros::MotorGroup right_side_motors({rightFront, rightFront, rightMiddle1, leftMiddle2});

pros::Imu inertial_sensor(1); 

pros::Controller master(pros::E_CONTROLLER_MASTER);

Drive EzTempChassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-17, -18, 19, -20}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{14, 13, -12, 11}

  // IMU Port
  ,1

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,2.75

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,1


  // Uncomment if using tracking wheels
  /*
  // Left Tracking Wheel Ports (negative port will reverse it!)
  // ,{1, 2} // 3 wire encoder
  // ,8 // Rotation sensor

  // Right Tracking Wheel Ports (negative port will reverse it!)
  // ,{-3, -4} // 3 wire encoder
  // ,-9 // Rotation sensor
  */

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);


lemlib::Drivetrain drivetrain (
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    8, // track width
    2.75, // wheel diameter
    450, // wheel rpm
    2 // chase power
);

lemlib::OdomSensors sensors (
    nullptr, 
    nullptr, 
    nullptr, 
    nullptr,
    &inertial_sensor // inertial sensor
);

// forward/backward PID
lemlib::ControllerSettings lateralController (
    0.45, // kP
    5, // kD
    1, // smallErrorRange
    80, // smallErrorTimeout
    3, // largeErrorRange
    300, // largeErrorTimeout
    7 // slew rate
);
 
// turning PID
lemlib::ControllerSettings angularController (
    5, // kP
    35, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    0 // slew rate
);

lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

void checkMotorsAndReturnTemperature() {
    std::vector<pros::Motor> motors1 = {
        leftFront, leftBack, leftMiddle1, leftMiddle2, rightFront, rightBack, rightMiddle1, rightMiddle2, intake
    };

    while (true) {
        double totalTemp = 0.0;
        int count = 0;

        for (auto& motor : motors1) {
            double temp = motor.get_temperature();
            if (temp == PROS_ERR_F) { // PROS_ERR_F is returned when the motor is unplugged
                master.set_text(0, 0, "Motor " + std::to_string(motor.get_port()) + " unplugged.");
                pros::delay(250);
                master.rumble("---");
            }

            if (count < 9) {
                totalTemp += temp;
            }
            ++count;
        }

        if (count == 0) master.set_text(0, 0, "No motors found.");

        double averageTempCelsius = totalTemp / count;
        double averageTempFahrenheit = averageTempCelsius * 9.0 / 5.0 + 32.0;
        master.set_text(0, 0, "Avg DT Temp: " + std::to_string(averageTempFahrenheit));

        pros::delay(1000);
    }
}


// inits
void default_constants() {
  EzTempChassis.pid_heading_constants_set(3, 0, 20);
  EzTempChassis.pid_drive_constants_set(10, 0, 100);
  EzTempChassis.pid_turn_constants_set(3, 0, 20);
  EzTempChassis.pid_swing_constants_set(5, 0, 30);

  EzTempChassis.pid_turn_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  EzTempChassis.pid_swing_exit_condition_set(300_ms, 3_deg, 500_ms, 7_deg, 750_ms, 750_ms);
  EzTempChassis.pid_drive_exit_condition_set(300_ms, 1_in, 500_ms, 3_in, 750_ms, 750_ms);

  EzTempChassis.slew_drive_constants_set(7_in, 80);
}

void modified_exit_conditions() {
  EzTempChassis.pid_turn_exit_condition_set(300_ms, 3_deg, 250_ms, 7_deg, 250_ms, 250_ms);
  EzTempChassis.pid_swing_exit_condition_set(300_ms, 3_deg, 250_ms, 7_deg, 250_ms, 250_ms);
  EzTempChassis.pid_drive_exit_condition_set(300_ms, 1_in, 250_ms, 3_in, 250_ms, 250_ms);
}

void calibrateBothChassis(bool isLemLib /* defaulted to false in the .h file */) {
    // calibrate the chassis with imu
    if (isLemLib) { chassis.calibrate(); } else { EzTempChassis.initialize(); }
}

void ezTempChassisInits() {
    // EZ temp inits
    EzTempChassis.opcontrol_curve_buttons_toggle(true); // Enables modifying the controller curve with buttons on the joysticks
    EzTempChassis.opcontrol_drive_activebrake_set(0); // Sets the active brake kP. We recommend 0.1.
    EzTempChassis.opcontrol_curve_default_set(7, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
    modified_exit_conditions(); // Set the drive to your own constants from autons.cpp!
}