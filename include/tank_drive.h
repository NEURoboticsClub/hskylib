#ifndef TANKDRIVE_H
#define TANKDRIVE_H

#include "api.h"

class TankDrive {
private:
    pros::MotorGroup leftMotorGroup = {};
    pros::MotorGroup rightMotorGroup = {};
    pros::Controller controller;

    // main function
    void tankDrive();

public:
    TankDrive(pros::MotorGroup& leftMotors,
        pros::MotorGroup& rightMotors,
        pros::Controller& ctrl,
        pros::motor_brake_mode_e brakeMode,
        pros::motor_gearset_e gearset);

    // initialize and start the task
    void initialize();
};

#endif
