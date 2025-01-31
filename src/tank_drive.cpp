#include "tank_drive.h"

// constructor
TankDrive::TankDrive(pros::MotorGroup& leftMotors,
    pros::MotorGroup& rightMotors,
    pros::Controller& ctrl,
    pros::motor_brake_mode_e brakeMode,
    pros::motor_gearset_e gearset)
        : controller(ctrl) {
            leftMotorGroup.append(leftMotors);
            rightMotorGroup.append(rightMotors);
            leftMotorGroup.set_brake_mode_all(brakeMode);
            rightMotorGroup.set_brake_mode_all(brakeMode);
            leftMotorGroup.set_gearing_all(gearset);
            rightMotorGroup.set_gearing_all(gearset);
}

void TankDrive::tankDrive() {
    while (true) {
        int leftSpeed = ((float)controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0) * getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing());
        int rightSpeed = ((float)controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0) * getInputExtremeForGearset((pros::motor_gearset_e) rightMotorGroup.get_gearing());

        rightMotorGroup.move(rightSpeed);
        leftMotorGroup.move(leftSpeed);

        pros::delay(20);
    }
}

void TankDrive::arcadeDrive() {
    while (true) {
        int forward = 0.4 * ((float)controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0) * getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing());
        int turn = 0.4* ((float)controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0) * getInputExtremeForGearset((pros::motor_gearset_e) rightMotorGroup.get_gearing());

        int leftSpeed = forward + turn;
        int rightSpeed = forward - turn;

        rightMotorGroup.move(rightSpeed);
        leftMotorGroup.move(leftSpeed);

        pros::delay(20);
    }
}

void TankDrive::initialize(DriveStyle driveStyle) {
    if (driveStyle == ARCADE) {
        pros::Task task([this] { arcadeDrive(); });
    } else if (driveStyle == TANK) {
        pros::Task task([this] { tankDrive(); });
    }
}
