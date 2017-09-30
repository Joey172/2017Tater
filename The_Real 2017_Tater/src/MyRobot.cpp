#include "WPILib.h"
#include "Shooter.h"
#include "RobotMap.h"
#include "UserInterface.h"
#include <iostream>
using namespace frc;
using namespace std;
//#include "TrapezoidalMove.h"

/**
 * This is a demo program showing the use of the RobotBase class.
 * The IterativeRobot class is the base of a robot application that will automatically call your
 * Periodic methods for each packet based on the mode.
 */ 
class RobotDemo : public IterativeRobot
{
	RobotDrive myRobot; 					// robot drive system
	//Joystick lStick, rStick, pickStick; 	// only joystick
	Solenoid forkDown, forkUp, arcReactor;

	Shooter shoot;
	UserInterface ui;
	struct TaterUserInput tui;
	bool m_autoFirst;
	bool paradeDrive;
	//Encoder lCode, rCode;
	//TrapezoidalMoveProfile autoMove;


public:
	RobotDemo(): 									// list initialization
		myRobot(LEFT_MOTOR_PWM, RIGHT_MOTOR_PWM),	// these must be initialized in the same order
		//lStick(LTANK_JOY_USB),						// as they are declared above.
		//rStick(RTANK_JOY_USB),
		//pickStick(SHOOTER_JOY_USB),
		forkDown(1, FORK_DN_SOL),
		forkUp(1, FORK_UP_SOL),
		arcReactor (1, ARC_RCTR_SOL),

	    shoot(),
	    ui(),
	    tui(),  // default to all zeros.
	    m_autoFirst(true),
	    paradeDrive(true)
		//lCode (1, CODE_LT_A, 1, CODE_LT_B, false),
		//rCode (1, CODE_RT_A, 1, CODE_RT_B, true),
		//autoMove(0.1, 0.1, 2.0, 15*12.0),
	  
	{
		myRobot.SetExpiration(0.3);
		//this->SetPeriod(0.02); 	//Set update period to sync with robot control packets (20ms nominal)
	}							//When set to zero, periodic tasks are called based on when DS packets come in
	
/**
 * Robot-wide initialization code should go here.
 * 
 * Use this method for default Robot-wide initialization which will
 * be called when the robot is first powered on.  It will be called exactly 1 time.
 */
void RobotInit() {
	printf("Robot Init");
	ui.Init();
	SmartDashboard::PutNumber("something", 0.13);
	SmartDashboard::PutNumber("firstShot", 0.000);
	SmartDashboard::PutNumber("delay", 0.000);
	SmartDashboard::PutNumber("secondShot", 0.000);
}

/**
 * Initialization code for disabled mode should go here.
 * 
 * Use this method for initialization code which will be called each time
 * the robot enters disabled mode. 
 */

void TeleopInit() {
	//lCode.Start();
	//rCode.Start();
	printf("Teleop Init");
	ui.Init();
	shoot.Init();
}

/**
 * Periodic code for teleop mode should go here.
 *
 * Use this method for code which will be called periodically at a regular
 * rate while the robot is in teleop mode.
 */
void TeleopPeriodic() {
	static bool frontDrive = true;

	//float voltage;
	ui.GetData(&tui); // update user interface structure "tater user interface"
	shoot.Run3(&tui);// check for button pushes and manange shots

	//choose front/back
	if (tui.frontDrive) {
		frontDrive = true;
		arcReactor.Set(false);	//de-activate arc-reactor
	}
	if (tui.revDrive) {
		frontDrive = false;
		arcReactor.Set(true);	//activate arc-reactor
	}


	/**
	 * Periodic code for disabled mode should go here.
	 *
	 * Use this method for code which will be called periodically at a regular
	 * rate while the robot is in disabled mode.
	 */

	
	if (frontDrive) {		//front is "forward"
		if (tui.turbo) {
			myRobot.TankDrive(-tui.leftVal, -tui.rightVal, true);	//with turbo
		}
		else {
			myRobot.TankDrive(-tui.leftVal*0.6, -tui.rightVal*0.6, true);	//without turbo
		}
	}
	if (!frontDrive) {		//rear is "forward"
		if (tui.turbo) {	
			myRobot.TankDrive(tui.rightVal, tui.leftVal, true);	//with turbo
		}
		else {
			myRobot.TankDrive(tui.rightVal*0.6, tui.leftVal*0.6, true);	//without turbo
		}	
	}
	if (tui.forkDown){
			forkDown.Set(true);
		}
	else {
		forkDown.Set(false);
	}

	if (tui.forkUp){
		forkUp.Set(true);
	}
	else {
		forkUp.Set(false);
	}
}
void DisabledInit() {
	printf("Disabled Init");
}
/**
 * Initialization code for test mode should go here.
 * 
 * Use this method for initialization code which will be called each time
 * the robot enters test mode.
 */
void TestInit() {
	printf("Test Init");
}

/**
 * Periodic code for test mode should go here.
 *
 * Use this method for code which will be called periodically at a regular
 * rate while the robot is in test mode.
 */
void TestPeriodic() {
	
	printf("Test Periodic");
}

};

START_ROBOT_CLASS(RobotDemo);

