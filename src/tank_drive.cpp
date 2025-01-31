#include "tank_drive.h"
#include "utils.h"

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

void TankDrive::initialize() {
    pros::Task task([this] { tankDrive(); });
}
