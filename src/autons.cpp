#include "devices.hpp"
#include "autons.hpp"
#include "drivercontrol.hpp"

void doNothing() {
    EzTempChassis.pid_drive_set(60, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(58);

    EzTempChassis.pid_drive_set(-60, 120, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-58);
}
// HAHAHAHAH Mr. Pierce is here he was here hahahahahahaha
// function definitions

//       chassis.setPose(x, y, theta); 
//       chassis.turnTo(x, y, timeout);    
//       chassis.follow(path file, timeout, lookahead distance, isAsynchronous, forwards (false makes the robot run the path backwards));
//
//       chassis.waitUntil(inches); use this to have your bot wait until the path is finished
//       a really big number means just wait until the path has finished


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;

void maintainOrientationTask(void* param) {
    while (true) {
        EzTempChassis.pid_turn_set(15, DRIVE_SPEED, false);
        EzTempChassis.drive_angle_set(15);
        // Code to maintain orientation goes here
        // For example, setting turn velocity to 0
        // Ensure you have some delay here to prevent the task from hogging CPU resources
        pros::delay(20); // Delay for 20ms to yield time to other tasks
    }
}

void skills() {
    //------------------
    //SKILLS START
    //------------------
    //Start with sled corner above tile intersection, left middle screw on tile line (-60 degrees).
    
    EzTempChassis.drive_angle_set(-60);

    intake = -127; //Drop intake

    //Score alliance triballs
    EzTempChassis.pid_drive_set(-30, 120, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-28);
    intake=0;
    //Back out of goal
    EzTempChassis.pid_drive_set(12, 120, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(10);
    //Turn to shoot
    EzTempChassis.pid_turn_set(15, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();
    //Back into matchload bar
    EzTempChassis.pid_drive_set(-8, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();
    // vertwing1.set_value(true);//Lock onto matchload bar
    
    //------------------
    //MATCHLOAD
    //------------------
    pros::Task orientationTask(maintainOrientationTask);
    // slapHang1.move_velocity(-110);
    // slapHang2.move_velocity(-55);    // setSlapHang(-80);
    pros::delay(24750);
    orientationTask.remove();
    // slapHang1.move_velocity(0);
    // slapHang2.move_velocity(0);    // setSlapHang(0);
    
    EzTempChassis.pid_turn_set(17, DRIVE_SPEED, false); 
    EzTempChassis.pid_wait();

    //--------------------
    //BEGIN CLOSE SIDE
    //----------------------
    EzTempChassis.drive_angle_set(17);     //Redudant Check

    pros::delay(500);

    // vertwing1.set_value(false); //Unlock from matchload bar
    intake=-127;
    //Go out from matchload bar
    EzTempChassis.pid_drive_set(20, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(18);
    //Swing to first triball
    EzTempChassis.pid_swing_set(RIGHT_SWING, -47, 110, 50);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-42);
    //Grab triball
    EzTempChassis.pid_drive_set(12, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(10);
    //Back up
    EzTempChassis.pid_drive_set(-16, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-14);
    //Swing parallel to barrier
    EzTempChassis.pid_swing_set(LEFT_SWING, 82, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(76);
    horzwing2.set_value(true);          //Right wing true
    intake = 127;                       //Outtake

    //Ram into short barrier
    EzTempChassis.pid_drive_set(64, DRIVE_SPEED, true);
    pros::delay(100);
    EzTempChassis.pid_wait_until(62);
    intake = 10;                        //intake to prevent jamming
    
    /*
    SECOND PUSH (cut for time)
    // Back up
    EzTempChassis.pid_drive_set(-13, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-5);

    intake = 127;                       //outtake
    EzTempChassis.pid_wait_until(-10);
    //Slow push over short barrier
    EzTempChassis.pid_drive_set(15, 40, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(13);
    pros::delay(100);
    */

    horzwing2.set_value(false);         //Right wing off

    //Turn backward
    EzTempChassis.pid_turn_set(175, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(173);
    intake = 0;                         // intake off
    EzTempChassis.pid_drive_set(3, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(1);
    horzwing2.set_value(true);
    //Swing around into aisle
    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 0, SWING_SPEED, 26);
    pros::delay(100);
    EzTempChassis.pid_wait_until(5);
    intake = 127;                       //outtake

    //-----------------
    //BEGIN FAR SIDE 
    //-----------------
    // Go down aisle
    EzTempChassis.pid_drive_set(72, DRIVE_SPEED, true);
    pros::delay(100);
    EzTempChassis.pid_wait_until(70);
    horzwing2.set_value(false);         //Right wing in
    horzwing1.set_value(true);          //Left wing out
    //Swing to goal short side
    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, -90, SWING_SPEED, 40);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-85);
    //Push into goal short side
    EzTempChassis.pid_drive_set(16, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(14);
    //Back up
    EzTempChassis.pid_drive_set(-12, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-9);
    //Repush
    EzTempChassis.pid_drive_set(17, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(14);
    //Back up
    EzTempChassis.pid_drive_set(-8, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-6);
    horzwing1.set_value(false);        //left wing off

    //--------------------
    //PUSH 1 SETUP woah
    //-------------------
    // Turn towards center
    EzTempChassis.pid_turn_set(-160, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-155);
    //Go to mid
    EzTempChassis.pid_drive_set(46, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(44);
    //Turn slightly to middle
    EzTempChassis.pid_turn_set(-200, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-195);
    intake = 0;

    //----------------
    //PUSH 1
    //----------------
    // toggleVertWings(); //Out
    //Push
    EzTempChassis.pid_drive_set(-40, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-37);
    //Back up
    EzTempChassis.pid_drive_set(14, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(11);
    //Repush
    EzTempChassis.pid_drive_set(-15, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-13);
    // toggleVertWings();          //off

    //------------------
    //PUSH 2 SETUP
    //------------------
    //Back up
    EzTempChassis.pid_drive_set(30, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(28);

    EzTempChassis.pid_turn_set(-270, DRIVE_SPEED,false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-265);

    // toggleVertWings();
    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, -180, SWING_SPEED, 35);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-185);

    //TURN SWITCHED TO SWING FOR TIME
    /*
    //Turn parallel to bar
    EzTempChassis.pid_turn_set(-270, DRIVE_SPEED,false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-265);
    //Go to middle
    EzTempChassis.pid_drive_set(-17, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-15);
    //Point to goal
    EzTempChassis.pid_turn_set(-180, -DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(177);
    toggleVertWings();                  //on
    */

    //-----------------
    //PUSH 2
    //-----------------
    //PUSH
    EzTempChassis.pid_drive_set(-33, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-31);
    //REPUSH
    EzTempChassis.pid_drive_set(14, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(11);
    EzTempChassis.pid_drive_set(-16, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-13);
    // toggleVertWings(); //off

    //---------------------
    //PUSH 3 SETUP
    //---------------------
    //Back up
    EzTempChassis.pid_drive_set(30, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(28);

     //Turn to left
    EzTempChassis.pid_turn_set(-265, DRIVE_SPEED, 40);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-270);

    //TURN SWITCHED TO SWING FOR TIME
    /*
    // EzTempChassis.pid_turn_set(-95, DRIVE_SPEED, 40);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-90);
    // //Go left
    // EzTempChassis.pid_drive_set(24, DRIVE_SPEED, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(21);
    // //Point to mid
    // EzTempChassis.pid_turn_set(-160, -DRIVE_SPEED);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-143);
    */

    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, -175, SWING_SPEED, 15);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-165);

    //-----------------
    //THIRD FRONT PUSH
    //-----------------
    //Push
    // toggleVertWings();
    EzTempChassis.pid_drive_set(-34, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-32);
    //Back up
    EzTempChassis.pid_drive_set(15, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(13);
    //Repush
    EzTempChassis.pid_drive_set(-17, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-15);

    //-------------
    //C PUSH SETUP
    //-------------
    EzTempChassis.pid_drive_set(20, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(18);
    // toggleVertWings(); //off
    toggleHorzWings(); //off

    //Turn to diagonal
    EzTempChassis.pid_turn_set(-60, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-65);
    //Go down diagonal
    EzTempChassis.pid_drive_set(18, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(16);
    toggleHorzWings();          //on
    intake = 20;

    //------------
    //C PUSH
    //------------
    EzTempChassis.pid_swing_set(ez::LEFT_SWING, 90, DRIVE_SPEED, 40);
    pros::delay(100);
    EzTempChassis.pid_wait_until(133);

    intake = 0;

    EzTempChassis.pid_drive_set(15, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(12);

    EzTempChassis.pid_drive_set(-15, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(12);

    intake=127;
    EzTempChassis.pid_drive_set(15, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-12);

    EzTempChassis.pid_drive_set(-15, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-12);
}

//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------
//Match AUTOS
//----------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------




// ===================================
// Left Side Autons
// ===================================

// example auto for clearing matchload area and touching pole
void leftSideQualOld() {
    intake = 127;
    EzTempChassis.pid_drive_set(-13, DRIVE_SPEED,false);
    pros::delay(400);
    intake = 0;
    EzTempChassis.pid_wait_until(-12);

    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 45, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();
    //push in preload
    EzTempChassis.pid_drive_set(-12.45, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait();


    EzTempChassis.pid_drive_set(11.15, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(-135, 60, true);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-4, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_swing_set(ez::LEFT_SWING, -180, 80);
    pros::delay(200);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-18, 80, false);
    // vertwing1.set_value(true);
    pros::delay(100);
    EzTempChassis.pid_wait();


    EzTempChassis.pid_drive_set(4, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();
    // vertwing1.set_value(false);

    //Sweep matchload ball
    EzTempChassis.pid_swing_set(ez::LEFT_SWING, -225, 60); //Turns and pushes the ball out
    pros::delay(100);
    EzTempChassis.pid_wait();


    // //Go down aisle
    EzTempChassis.pid_drive_set(-35, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(30);
    EzTempChassis.pid_drive_set(9.5, DRIVE_SPEED, false);
    EzTempChassis.pid_wait_until(6);
    EzTempChassis.pid_turn_set(-45, TURN_SPEED, false);
    EzTempChassis.pid_wait();
    pros::delay(400);
    //touch bar
    EzTempChassis.pid_drive_set(14, DRIVE_SPEED, false);
    EzTempChassis.pid_wait();
    intake = 127;

    pros::delay(5000);
    intake = 0;
}

void leftSideQual(){
    EzTempChassis.drive_angle_set(-74);
    toggleHorzWings();
    //Rush midball
    EzTempChassis.pid_drive_set(49, 127, true);
    pros::delay(100);
    EzTempChassis.pid_wait_until(3);
    toggleHorzWings();
    intake = -127;              //intake
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-55, 118, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(0, TURN_SPEED, false);
    EzTempChassis.pid_wait();

    intake=127;                 //outtake
    pros::delay(400);

//BAR
    EzTempChassis.pid_turn_set(26, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();
    intake=0;

    EzTempChassis.pid_drive_set(-19, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();
    
    EzTempChassis.pid_turn_set(38, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

// Get Matchload ball
    toggleHorzWings();

    EzTempChassis.pid_drive_set(11, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(0, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(20);
    toggleHorzWings();
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(38, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(36);
    

    EzTempChassis.pid_drive_set(10, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(8);

    EzTempChassis.pid_turn_set(1, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();
    intake=127;

    EzTempChassis.pid_drive_set(36, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    toggleHorzWings();

    pros::delay(3000);
    intake=0;
}


void leftSideElimsBowlSetup() {
    EzTempChassis.drive_angle_set(-77);
    // Get mid ball 

    horzwing1.set_value(true);
    EzTempChassis.pid_drive_set(52, 127, false);

    EzTempChassis.pid_wait_until(25);
    horzwing1.set_value(false);
    intake = -127;
    // horzwing.set_value(false);
    // EzTempChassis.pid_wait_until(42);
    // EzTempChassis.pid_drive_set(15, 127, false);
    EzTempChassis.pid_wait_until(50);

    EzTempChassis.pid_drive_set(-8, DRIVE_SPEED, false);
    pros::delay(100);

    EzTempChassis.pid_wait_until(-5);
    
    EzTempChassis.pid_turn_set(-180, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-178);

    EzTempChassis.pid_drive_set(18, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(16);

    EzTempChassis.pid_turn_set(-90, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-92);

    pros::delay(100);


    EzTempChassis.pid_drive_set(-28, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-26);

    EzTempChassis.pid_drive_set(5, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(3);

    EzTempChassis.pid_turn_set(90, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(87);

    intake=127;

    EzTempChassis.pid_drive_set(7, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(5);

    EzTempChassis.pid_swing_set(LEFT_SWING, 70, -127, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(67);

    EzTempChassis.pid_turn_set(135, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(133);

    EzTempChassis.pid_drive_set(22, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(20);

    EzTempChassis.pid_swing_set(RIGHT_SWING, 90, 127, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(92);

    horzwing2.set_value(true);

    EzTempChassis.pid_turn_set(0, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(2);

    pros::delay(100);

    EzTempChassis.pid_turn_set(10, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(8);

    EzTempChassis.pid_swing_set(RIGHT_SWING, 0, 127, 30);
    pros::delay(100);
    EzTempChassis.pid_wait_until(2);

    intake=127;

    EzTempChassis.pid_drive_set(34, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(32);

    pros::delay(100);

    EzTempChassis.pid_drive_set(-34, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-32);

}

// DISRUPT ELIM AUTO
void leftSideElimsDisrupt() {
    EzTempChassis.drive_angle_set(-77);
    // Get mid ball 

    horzwing1.set_value(true);
    EzTempChassis.pid_drive_set(52, 127, false);

    EzTempChassis.pid_wait_until(25);
    horzwing1.set_value(false);
    intake = -127;
    // horzwing.set_value(false);
    // EzTempChassis.pid_wait_until(42);
    // EzTempChassis.pid_drive_set(15, 127, false);
    EzTempChassis.pid_wait_until(50);


    // Turn to push 2 balls over to the other side
    EzTempChassis.pid_drive_set(-6, DRIVE_SPEED, false);
    pros::delay(100);

    EzTempChassis.pid_wait_until(-3);
    
    EzTempChassis.pid_turn_set(-180, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-178);

    toggleHorzWings();

    intake=127;
    EzTempChassis.pid_drive_set(20, DRIVE_SPEED, false);
    pros::delay(100);

    EzTempChassis.pid_wait_until(18);

    EzTempChassis.pid_drive_set(-11, DRIVE_SPEED, false);
    pros::delay(100);

    EzTempChassis.pid_wait_until(-9);

    EzTempChassis.pid_drive_set(13, DRIVE_SPEED, false);
    pros::delay(100);

    EzTempChassis.pid_wait_until(11);

    EzTempChassis.pid_drive_set(-20, DRIVE_SPEED, false);
    pros::delay(100);

    EzTempChassis.pid_wait_until(-18);

    intake=0;

    EzTempChassis.pid_turn_set(-77, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-79);

    //Go back to the origin
    EzTempChassis.pid_drive_set(-55, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-53);

    toggleHorzWings();
    pros::delay(200);
    EzTempChassis.pid_turn_set(-352, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-350);
    toggleHorzWings();


//Old BAR Code
    // EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 115, -DRIVE_SPEED);
    // pros::delay(100);
    // EzTempChassis.pid_wait();

    // EzTempChassis.pid_drive_set(-18, DRIVE_SPEED, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-16);

    // EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 161, -DRIVE_SPEED);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(159);
    
    // //score alliance triball
    // EzTempChassis.pid_drive_set(-11.25, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait();
    // pros::delay(200);

    // EzTempChassis.pid_drive_set(3, DRIVE_SPEED, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait();

    // EzTempChassis.pid_drive_set(-6, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait();
    // pros::delay(200);

    // EzTempChassis.pid_drive_set(7, DRIVE_SPEED, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait();

    // EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 115, -DRIVE_SPEED);
    // pros::delay(100);
    // EzTempChassis.pid_wait();

    // EzTempChassis.pid_drive_set(17, 70, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait();
    // intake = 127;

    // EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 75, -DRIVE_SPEED);
    // pros::delay(100);
    // EzTempChassis.pid_wait();
//Go down aisle
    EzTempChassis.pid_drive_set(35, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-40, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();
    pros::delay(5000);
    intake = 0;

}


// =====================================================
// RIGHT SIDE AUTONS 
// =====================================================

void rightSideQuals() {
    // lower intake
    intake = -127;

    EzTempChassis.pid_drive_set(-12, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_swing_set(ez::LEFT_SWING, -45, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-17, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(13, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_swing_set(ez::LEFT_SWING, 0, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(20, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_swing_set(ez::LEFT_SWING, 45, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(40, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-30, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(225, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(8, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    // toggleVertWings();
    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 180, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(12, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(135, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();
    // toggleVertWings();

    EzTempChassis.pid_drive_set(-6, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(180, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    intake = 127;
    EzTempChassis.pid_drive_set(20, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 135, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(16, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 180, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-22, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-20);

    EzTempChassis.pid_turn_set(97, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(95);

    intake = -127;
    EzTempChassis.pid_drive_set(57, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(55);

    EzTempChassis.pid_turn_set(227, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(225);

    EzTempChassis.pid_drive_set(48, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(12);
    intake = 127;
    EzTempChassis.pid_wait();
}

void rightSideQualsTouchBar() {
    // lower intake
    intake = -127;

    EzTempChassis.pid_drive_set(-12, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_swing_set(ez::LEFT_SWING, -45, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-17, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(13, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_swing_set(ez::LEFT_SWING, 0, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(20, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_swing_set(ez::LEFT_SWING, 45, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(40, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-30, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(225, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(8, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    // toggleVertWings();
    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 180, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(12, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(135, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();
    // toggleVertWings();

    EzTempChassis.pid_drive_set(-6, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_turn_set(180, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait();

    intake = 127;
    EzTempChassis.pid_drive_set(20, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 137, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(135);

    EzTempChassis.pid_drive_set(16, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-12, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-10);


    EzTempChassis.pid_turn_set(47, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(45);

    intake = 0;
    EzTempChassis.pid_drive_set(52, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(50);

    // toggleVertWings();
    EzTempChassis.pid_turn_set(92, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(90);
}


void rightSideFarRush() {

    // Rush the Center
    EzTempChassis.drive_angle_set(60);
    // toggleHorzWings();
    horzwing2.set_value(true);
    EzTempChassis.pid_drive_set(63, 127, false);
    EzTempChassis.pid_wait_until(10);
    horzwing2.set_value(false);
    // toggleHorzWings();
    EzTempChassis.pid_wait_until(30);
    intake=-127;
    pros::delay(100);
    EzTempChassis.pid_wait_until(61);

    // OPTIONAL CODE 
    // Optional to back up before turning towards the goal to avoid disruptions

    // EzTempChassis.pid_drive_set(-8, DRIVE_SPEED, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-6);

    // EzTempChassis.pid_swing_set(ez::LEFT_SWING, 181, DRIVE_SPEED);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(178);

    // EzTempChassis.pid_drive_set(32, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(12);
    // intake = 127;
    // EzTempChassis.pid_wait_until(30);

    // Turn to face goal after first ball

    EzTempChassis.pid_turn_set(180, 127);
    pros::delay(100);
    EzTempChassis.pid_wait_until(175);

    toggleHorzWings();

    EzTempChassis.pid_drive_set(32, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(12);
    intake = 127;
    EzTempChassis.pid_wait_until(30);
    

    EzTempChassis.pid_drive_set(-6, DRIVE_SPEED, false);
    EzTempChassis.pid_wait_until(-4);
    toggleHorzWings();
    //turn to get 3rd triball
    EzTempChassis.pid_turn_set(-32, -DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-30);

    intake = -127;
    //go get 3rd triball
    EzTempChassis.pid_drive_set(28, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(26);

    EzTempChassis.pid_drive_set(-22, 110, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-20);
    //turn to goal
    EzTempChassis.pid_turn_set(175, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(170);

    intake=127;
    horzwing1.set_value(true);
    // toggleVertWings();
    EzTempChassis.pid_drive_set(17, 127, false);
    EzTempChassis.pid_wait_until(15);
    // toggleVertWings();

    EzTempChassis.pid_drive_set(-5, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-3);
    horzwing1.set_value(false);


    EzTempChassis.pid_turn_set(90, TURN_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(85);

    EzTempChassis.pid_drive_set(-46, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-44);

    //turn towards matchload
    EzTempChassis.pid_turn_set(180, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(177);

    // EzTempChassis.pid_drive_set(25, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(10);
    // intake = -127;
    // EzTempChassis.pid_wait_until(23);
    // pros::delay(100);

    // EzTempChassis.pid_drive_set(-34, 110, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-32);

    EzTempChassis.pid_drive_set(8, 110, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(6);

   

    //turn along bar
    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 135, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(138);

    EzTempChassis.pid_drive_set(14, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(8);
    horzwing2.set_value(true);
    
    EzTempChassis.pid_wait_until(12);

    //sweep matchlaod
    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 90, DRIVE_SPEED);
    pros::delay(100);
    EzTempChassis.pid_wait_until(93);

    intake = 127;

    // Push into goal
    EzTempChassis.pid_drive_set(16, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(14);
    horzwing2.set_value(false);

    EzTempChassis.pid_drive_set(-14, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-12);
    

    // EzTempChassis.pid_turn_set(95, DRIVE_SPEED);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(90);
    
    
    // Repush into goal
    toggleHorzWings();
    EzTempChassis.pid_drive_set(16, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait();

    EzTempChassis.pid_drive_set(-8, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-5);
    toggleHorzWings();

    // Swing towards center to let defensive player bowl
    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 230, -DRIVE_SPEED, 100);
    pros::delay(100);
    EzTempChassis.pid_wait();

    // EzTempChassis.pid_drive_set(-16, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-14);

    
}

void rightSide6Ball() {
    // New 6 ball
    EzTempChassis.pid_drive_set(6, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(4);

    intake = -127;
    pros::delay(300);

    EzTempChassis.pid_drive_set(-30, DRIVE_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-27);
    

    EzTempChassis.pid_swing_set(ez::LEFT_SWING, -94, SWING_SPEED, 35);
    EzTempChassis.pid_wait_until(-20);
    toggleHorzWings();
    EzTempChassis.pid_wait_until(-90);

    // Get Matchload

    // toggleHorzWings();
    // EzTempChassis.pid_drive_set(-18, 88, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-16);


    // EzTempChassis.pid_swing_set(ez::LEFT_SWING, -90, DRIVE_SPEED);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-88);

    toggleHorzWings();

    // Pull out matchload
    EzTempChassis.pid_drive_set(-24, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-21);

    EzTempChassis.pid_drive_set(15, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(13);

    EzTempChassis.drive_angle_set(-90);


    //REPUSH
    // EzTempChassis.pid_drive_set(-16, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-14);

    // EzTempChassis.pid_drive_set(8, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(6);
    // toggleVertWings();

    // Turn and put other in goal
    

    // EzTempChassis.pid_turn_set(-70, TURN_SPEED, false); //push at angle
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-65);

    // //push in two triballs
    // EzTempChassis.pid_drive_set(-25, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-23);

    // EzTempChassis.pid_drive_set(20, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(18);


    EzTempChassis.pid_turn_set(97, TURN_SPEED, false); //push at angle
    pros::delay(100);
    EzTempChassis.pid_wait_until(94);
    intake = 127;

    // toggleHorzWings();
    
    EzTempChassis.pid_drive_set(20, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(18);

    intake = 0;
    // toggleHorzWings();
    // Turn towards middle
    EzTempChassis.pid_drive_set(-11, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-9);
    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 16, -110, -78);
    pros::delay(100);
    EzTempChassis.pid_wait_until(18);

    // Get the side middle
    intake=-127;
    EzTempChassis.pid_drive_set(48, DRIVE_SPEED, true);
    pros::delay(100);
    EzTempChassis.pid_wait_until(45);
    intake=0;
    EzTempChassis.pid_drive_set(-5, DRIVE_SPEED, true);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-3);


    EzTempChassis.pid_turn_set(160, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(155);
    intake=127; // outtake
    pros::delay(300);

    EzTempChassis.pid_turn_set(70, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(65);

    intake=-127;//intake

    EzTempChassis.pid_drive_set(26, 110, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(23);

    pros::delay(100);

    EzTempChassis.pid_turn_set(170, TURN_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(167);

    toggleHorzWings();

    // Push into goal
    intake=127;
    EzTempChassis.pid_drive_set(36, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(34);

    toggleHorzWings();

    intake=0;

    EzTempChassis.pid_drive_set(-20, 127, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(-17);

    EzTempChassis.pid_turn_set(315, TURN_SPEED, false);
    pros::delay(100);
    EzTempChassis.pid_wait_until(310);

    EzTempChassis.pid_swing_set(ez::RIGHT_SWING, 280, 127, 100);
    pros::delay(100);
    EzTempChassis.pid_wait_until(290);

    toggleHorzWings();

    // REPUSH
    //  EzTempChassis.pid_drive_set(13, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(10);

    // EzTempChassis.pid_drive_set(-12, 127, false);
    // pros::delay(100);
    // EzTempChassis.pid_wait_until(-10);

}

