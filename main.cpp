#include "robot-config.h"
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description: Competition template for VCS VEX V5                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/

//Creates a competition object that allows access to Competition methods.
vex::competition    Competition;
controller Controller = controller();
// - Helper Variables - 

double circumference = 12.5663;
// - Helper Functions - 
void driveLeft(){
    int scaledPower {Controller.Axis3.value() + Controller.Axis4.value()};
    if (abs(scaledPower) < 5)
        scaledPower = 0;
    else
        scaledPower = ( (scaledPower^3/100) * scaledPower ) / 100;
    
    if (Controller.Axis3.value() + Controller.Axis4.value() < 0)
        scaledPower = scaledPower * -1;
    else
        scaledPower = scaledPower *  1;
    fDriveL.spin(directionType::fwd, scaledPower, velocityUnits::pct);
    rDriveL.spin(directionType::fwd, scaledPower, velocityUnits::pct);
}

void driveRight(){
    int scaledPower {Controller.Axis4.value() - Controller.Axis3.value()};
    if (abs(scaledPower) < 5)
        scaledPower = 0;
    else
        scaledPower = ( (scaledPower^3/100) * scaledPower ) / 100;
    
    if (Controller.Axis4.value() - Controller.Axis3.value() < 0)
        scaledPower = scaledPower * -1;
    else
        scaledPower = scaledPower *  1;
    fDriveR.spin(directionType::fwd, scaledPower, velocityUnits::pct);
    rDriveR.spin(directionType::fwd, scaledPower, velocityUnits::pct);
}
static bool reverse {false};
static bool toggle {false};
static bool toggleReverse {false};
static int mode {1}; 

void toggleIntake()
{
    toggle = !toggle;

    if (toggle)
        intake.spin(directionType::fwd, 100, velocityUnits::pct);
    else
       intake.spin(directionType::fwd, 0, velocityUnits::pct);
}
void toggleIntakeReverse()
{
    toggleReverse = !toggleReverse;

    if (toggleReverse)
        intake.spin(directionType::fwd, -100, velocityUnits::pct);
    else
       intake.spin(directionType::fwd, 0, velocityUnits::pct);
}


void puIntake()
    {intake.spin(directionType::fwd, 100, velocityUnits::pct);}
void pdIntake()
{
    intake.spin(directionType::fwd, 0, velocityUnits::pct);
    reverse = false;
}
void rIntake()
{
    intake.spin(directionType::fwd, -100, velocityUnits::pct);
    reverse = true;
}

void puIndexer()
    {indexer.spin(directionType::fwd, 100, velocityUnits::pct);}
void pdIndexer()
    {indexer.spin(directionType::fwd, 0, velocityUnits::pct);}
void rIndexer()
    {indexer.spin(directionType::fwd, -100, velocityUnits::pct);}



//Left Joystick Split Arcade - Non-Linearized Control
/*
void nlDrive_rSplitArcade()
{
    int speed = ( Controller1.Axis3.value() - Controller1.Axis1.value() ) / 2;
    if (abs(speed) < 5)
        speed = 0;
    else
        speed = ( (speed^2/100) * speed ) / 100;
    
    if ((( Controller1.Axis3.value() - Controller1.Axis1.value() ) / 2) < 0)
        speed = speed * -1;
    else
        speed = speed *  1;
    
    fDriveR.spin(directionType::fwd, speed, velocityUnits::pct);
    rDriveR.spin(directionType::fwd, speed, velocityUnits::pct);
}

*/
void moveRightDrive(int percent)
{
    fDriveR.spin(directionType::fwd, percent, velocityUnits::pct);
    rDriveR.spin(directionType::fwd, percent, velocityUnits::pct);

    }
void moveLeftDrive(int percent){
    fDriveL.spin(directionType::fwd, percent, velocityUnits::pct);
    rDriveL.spin(directionType::fwd, percent, velocityUnits::pct);
    }
void moveLeftDrivePID(double inches){
    double degrees = inches/circumference * 360.0;
    fDriveL.rotateFor(degrees,rotationUnits::deg,150,velocityUnits::rpm,false);
    rDriveL.rotateFor(degrees,rotationUnits::deg,150,velocityUnits::rpm,false);
    
    }
void driveStraightPID(double inches){
    double degrees = inches/circumference * 360.0;
    fDriveR.startRotateFor(degrees,rotationUnits::deg,150,velocityUnits::rpm);
    fDriveL.startRotateFor(degrees,rotationUnits::deg,150,velocityUnits::rpm);
    rDriveL.startRotateFor(degrees,rotationUnits::deg,150,velocityUnits::rpm);
    rDriveR.startRotateFor(degrees,rotationUnits::deg,150,velocityUnits::rpm);
    }
void rotatePID(double degrees){
    
    fDriveR.startRotateFor(degrees,rotationUnits::deg,150,velocityUnits::rpm);
    fDriveL.startRotateFor(-degrees,rotationUnits::deg,150,velocityUnits::rpm);
    rDriveL.startRotateFor(-degrees,rotationUnits::deg,150,velocityUnits::rpm);
    rDriveR.startRotateFor(degrees,rotationUnits::deg,150,velocityUnits::rpm);
    }
void setHighVelocity(){
    flywheel.spin(directionType::fwd,170.0,velocityUnits::rpm);
}
void setLowVelocity(){
    flywheel.spin(directionType::fwd,190.0,velocityUnits::rpm);
}
void flywheelBrake(){
    flywheel.spin(directionType::fwd,120.0,velocityUnits::rpm);
     /*if(flywheel.velocity(velocityUnits::rpm) > 120.0){
             flywheel.stop(brakeType::coast);
         } else if(flywheel.velocity(velocityUnits::rpm) < 120.0 || flywheel.velocity(velocityUnits::rpm) == 120.0 ) {
             flywheel.setVelocity(120.0,velocityUnits::rpm);
          */   
         }

static bool highVelocityToggle {false};
void toggleHighVelocity()
{
    highVelocityToggle = !highVelocityToggle;

    if (highVelocityToggle)
        setHighVelocity();
    else
       flywheelBrake();
}

static bool lowVelocityToggle {false};
void toggleLowVelocity()
{
    lowVelocityToggle = !lowVelocityToggle;

    if (lowVelocityToggle)
        setLowVelocity();
    else
       flywheelBrake();
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the cortex has been powered on and    */ 
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton( void ) {
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/
int printRPM()
{
    int prm {0};
    while(1)
    {
        prm = flywheel.velocity(velocityUnits::rpm);
        Controller.Screen.print(prm);
        
    }
}
void autonomous( void ) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
    /*
    fDriveR.setRotation(0.0,rotationUnits::deg);
    rDriveR.setRotation(0.0,rotationUnits::deg);
    fDriveL.setRotation(0.0,rotationUnits::deg);
    rDriveL.setRotation(0.0,rotationUnits::deg);
    */
    int counter {0};
    flywheel.spin(directionType::fwd,170.0,velocityUnits::rpm);
   /* while(flywheel.velocity(velocityUnits::rpm)){
        counter++;
    intake.spin(directionType::fwd,150.0,velocityUnits::rpm);
    indexer.spin(directionType::fwd,150.0,velocityUnits::rpm);
    }*/
    
    while(flywheel.velocity(velocityUnits::rpm) < 170.0) {
        this_thread::sleep_for(10);
    }
    this_thread::sleep_for(200);
    
    intake.spin(directionType::fwd,100.0,velocityUnits::pct);
    indexer.spin(directionType::fwd,100.0,velocityUnits::pct);
    this_thread::sleep_for(2000);
    intake.stop(brakeType::coast);
    indexer.stop(brakeType::coast);
    driveStraightPID(44.0);
    while(fDriveL.rotation(rotationUnits::deg) < 40/circumference * 360.0) {
        this_thread::sleep_for(10);
    }
    this_thread::sleep_for(200);
   /* driveStraightPID(-36.0);
    while(fDriveL.rotation(rotationUnits::deg) < -36/circumference * 360.0) {
        this_thread::sleep_for(10);
    }
    this_thread::sleep_for(200);
    rotatePID(90.0);
    while(fDriveL.rotation(rotationUnits::deg) < 90) {
        this_thread::sleep_for(10);
    }  
      this_thread::sleep_for(200);
    toggleIntakeReverse();
    driveStraightPID(52.0);*/
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol( void ) {
  // User control code here, inside the loop
  while (1) {
    // This is the main exec ution loop for the user control program.
    // Each time through theloop your program should update motor + servo 
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to 
    // update your motors, etc.
    // ........................................................................
    Controller.ButtonL1.pressed(toggleIntake);
    Controller.ButtonL2.pressed(toggleIntakeReverse);//> intake toggle
    Controller.ButtonUp.pressed(puIndexer);
    Controller.ButtonUp.released(pdIndexer);
    //Flywheel Control
    Controller.ButtonR1.pressed(toggleHighVelocity);
      Controller.ButtonR2.pressed(toggleLowVelocity);
    
    
      //Drive Train - Tank Control Non Linear Control
    while(1){
        driveLeft();
        driveRight();  
    }
     
         
     
        
     }
    
    vex::task::sleep(20); //Sleep the task for a short amount of time to prevent wasted resources. 
  }



// Main will set up the competition functions and callbacks.
//
int main() {
    
    //Run the pre-autonomous function. 
    pre_auton();
    
    //Set up callbacks for autonomous and driver control periods.
    Competition.autonomous( autonomous );
    Competition.drivercontrol( usercontrol );

    //Prevent main from exiting with an infinite loop.                        
    while(1) {
      vex::task::sleep(100);//Sleep the task for a short amount of time to prevent wasted resources.
    }    
       
}
