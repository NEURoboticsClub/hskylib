#include "transport.h"
#include "utils.h"

// constructor
Transport::Transport(pros::MotorGroup& leftMotors,
    pros::MotorGroup& rightMotors,
    pros::Controller& ctrl,
    pros::motor_brake_mode_e brakeMode,
    pros::motor_gearset_e gearset,
    pros::controller_digital_e_t inButton,
    pros::controller_digital_e_t outButton,
    double motorDutyCycle)
        : inToggle(ctrl, inButton), outToggle(ctrl, outButton) {
            leftMotorGroup.append(leftMotors);
            rightMotorGroup.append(rightMotors);
            leftMotorGroup.set_brake_mode_all(brakeMode);
            rightMotorGroup.set_brake_mode_all(brakeMode);
            leftMotorGroup.set_gearing_all(gearset);
            rightMotorGroup.set_gearing_all(gearset);
            motorDutyCycle = motorDutyCycle;
}

void Transport::runTransport() {
    while (true) {
        inToggle.update();
        outToggle.update();
        if (inToggle.getCurrentState()) {
            moveIn();
        } else if (outToggle.getCurrentState()) {
            moveOut();
        } else {
            stop();
        }
        pros::delay(20);
    }
}

void Transport::initialize() {
    pros::Task task([this] { runTransport(); });
}

void Transport::moveIn() {
    uint16_t speed = motorDutyCycle * getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing());
    rightMotorGroup.move_velocity(speed);
    leftMotorGroup.move_velocity(speed);
}

void Transport::moveOut() {
    uint16_t speed = motorDutyCycle * getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing());
    rightMotorGroup.move_velocity(-speed);
    leftMotorGroup.move_velocity(-speed);
}

void Transport::stop() {
    rightMotorGroup.brake();
    leftMotorGroup.brake();
}
