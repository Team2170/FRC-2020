// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.

#include "Robot.h"

#include "frc/commands/Scheduler.h"
#include "frc/smartdashboard/SmartDashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableEntry.h"
#include "networktables/NetworkTableInstance.h"
#include "networktables/EntryListenerFlags.h"


	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
std::shared_ptr<DriveTrain> Robot::driveTrain;
std::shared_ptr<Intake> Robot::intake;
std::unique_ptr<OI> Robot::oi;

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INITIALIZATION
bool Robot::PracticeBot;
bool Robot::TankDrive;
bool Robot::RioCamera;

// used to calculate distance from the target
const double powerportVisionTargetHeight = (8 + 2.25/12) + (1 + 5.0/12)/2; // height of the center of the vision target (ft)
const double startingCameraHeight = 2; // height that the camera is mounted at (ft)
const double startingCameraAngle = 40; // angle camera is mounted at from horizontal (degrees)

// network table entries
nt::NetworkTableEntry ty;
nt::NetworkTableEntry cameraHeight;
nt::NetworkTableEntry cameraAngle;
nt::NetworkTableEntry targetHeight;
nt::NetworkTableEntry distance;

/**
 * @brief Initializes the robot
 * 
 * 1. Make sure all joysticks are plugged in for the selected driveMode
 * 2. Check if the robot is the PracticeBot
 * 3. Check if any cameras can be used
 * 4. Reset all OI objects/pointers
 * 
 */
void Robot::RobotInit() {
	int DriveMode = frc::Preferences::GetInstance()->GetInt("Drive Mode", 1);
	if (DriveMode == 0 || DriveMode == 2) {
		TankDrive = true;
		printf("Tank Drive - plug in extra joystick\n");
	}
	else {
		TankDrive = false;
	}
	PracticeBot  = frc::Preferences::GetInstance()->GetBoolean("Practice Bot", false);
	if (!Robot::PracticeBot) {			// Practice bot has no intake
		printf("Competition Bot Mode\n");
    	intake.reset(new Intake());
	}
	else {
		printf("Practice Bot Mode\n");
	}
	RioCamera = frc::Preferences::GetInstance()->GetBoolean("Rio Camera", false);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    driveTrain.reset(new DriveTrain());

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// This MUST be here. If the OI creates Commands (which it very likely
	// will), constructing it during the construction of CommandBase (from
	// which commands extend), subsystems are not guaranteed to be
	// yet. Thus, their requires() statements may grab null pointers. Bad
	// news. Don't move it.

	oi.reset(new OI());

	// Add commands to Autonomous Sendable Chooser
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS



    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=AUTONOMOUS
	if (RioCamera) {
		cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture();
		camera.SetResolution(160, 120);
		camera.SetFPS(10);
	}

	// Code for limelight network tables
	auto table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
	
	ty = table->GetEntry("ty");
	cameraHeight = table->GetEntry("camera height");
	cameraHeight.SetDouble(startingCameraHeight);
	cameraAngle = table->GetEntry("camera angle");
	cameraAngle.SetDouble(startingCameraAngle);
	targetHeight = table->GetEntry("target height");
	targetHeight.SetDouble(powerportVisionTargetHeight);
	distance = table->GetEntry("distance to target");
	distance.SetDouble(0);

	initRobot = new InitRobot();
}

/**
 * This function is called when the disabled button is hit.
 * You can use it to reset subsystems before shutting down.
 */
void Robot::DisabledInit(){

}

/**
 * @brief This function is called periodcally while the robot is disabled
 * 
 * In our case, all elevator zero positions are being updated.
 * 
 */
void Robot::DisabledPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

/**
 * @brief This function is called once when the robot is autonomous mode
 * 
 * In our case, the initRobot command group is called
 * 
 */
void Robot::AutonomousInit() {
	// No autonomous commands (although we could have made initRobot an autonomous commmand)
	// autonomousCommand = chooser.GetSelected();
	// if (autonomousCommand != nullptr)
	// 	autonomousCommand->Start();
	initRobot->Start();
}

/**
 * @brief This function is called periodically when the robot is autonomous mode
 * 
 * In our case, the scheduler is run.
 * 
 */
void Robot::AutonomousPeriodic() {
	frc::Scheduler::GetInstance()->Run();
}

/**
 * @brief This function is called once in teleop mode
 */
void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// these lines or comment it out.
//	if (autonomousCommand != nullptr)
//		autonomousCommand->Cancel();
initRobot->Start();
	
}

/**
 * Calculates distance (ft) from the target using the ty variable from the limelight camera.
 * Assumes tx is 0 and robot is already aligned with target.
 */
double calcDistanceFromTarget() {
	double heightOfTarget = targetHeight.GetDouble(powerportVisionTargetHeight);
	double heightOfCamera = cameraHeight.GetDouble(startingCameraHeight);
	double angleOfCamera = cameraAngle.GetDouble(startingCameraAngle);
	double angleToTarget = ty.GetDouble(0);
	double totalAngle = (angleOfCamera + angleToTarget) * 3.14159/180;
    return (heightOfTarget - heightOfCamera) / tan(totalAngle);
}


/**
 * @brief This function is called periodically in teleop mode
 */
void Robot::TeleopPeriodic() {
	distance.SetDouble(calcDistanceFromTarget());
	frc::Scheduler::GetInstance()->Run();
}

#ifndef RUNNING_FRC_TESTS
int main(int argc, char** argv) {
    return frc::StartRobot<Robot>();
}
#endif
