// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef OI_H
#define OI_H

#include "frc/WPILib.h"

class OI {
private:
	std::shared_ptr<frc::JoystickButton> counterClockwiseTurn;
	std::shared_ptr<frc::JoystickButton> clockwiseTurn;

	std::shared_ptr<frc::XboxController> driverJoystick;
	std::shared_ptr<frc::XboxController> operatorJoystick;
	std::shared_ptr<frc::JoystickButton> joystickDriverButtonVisionLock;
	std::shared_ptr<frc::JoystickButton> joystickButtonIntake;

	std::shared_ptr<frc::JoystickButton> joystickDriverButtonForward;
	std::shared_ptr<frc::JoystickButton> joystickDriverButtonExposureToggle;

	std::shared_ptr<frc::JoystickButton> operatorDriverOverrideForward;
	std::shared_ptr<frc::JoystickButton> operatorDriverOverrideReverse;
	std::shared_ptr<frc::JoystickButton> operatorDriverOverrideTR;
	std::shared_ptr<frc::JoystickButton> operatorDriverOverrideTL; 
	//four buttons that move the robot at constant velocity.

public:
	OI();

	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<frc::XboxController> getDriverJoystick();
	std::shared_ptr<frc::XboxController> getPushbuttonPanel();

    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=PROTOTYPES

	std::shared_ptr<frc::XboxController> getOperatorJoystick();
};

#endif
