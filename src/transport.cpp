#include "transport.h"
#include "utils.h"

// constructor
Transport::Transport(std::vector<std::int8_t> leftMotors,
    std::vector<std::int8_t> rightMotors,
    pros::Controller& ctrl,
    pros::motor_brake_mode_e brakeMode,
    pros::motor_gearset_e gearset,
    pros::controller_digital_e_t inButton,
    pros::controller_digital_e_t outButton,
    double motorDutyCycle)
        : inToggle(ctrl, inButton),
        outToggle(ctrl, outButton),
        motorDutyCycle(motorDutyCycle),
        leftMotorGroup(leftMotors),
        rightMotorGroup(rightMotors) {
            leftMotorGroup.set_brake_mode_all(brakeMode);
            rightMotorGroup.set_brake_mode_all(brakeMode);
            leftMotorGroup.set_gearing_all(gearset);
            rightMotorGroup.set_gearing_all(gearset);
            intakeIn = false;
            intakeOut = false;
}

void Transport::moveIn() {
    int speed = (motorDutyCycle * (double)getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing()));
    rightMotorGroup.move(speed);
    leftMotorGroup.move(speed);
}

void Transport::moveOut() {
    int speed = (motorDutyCycle * (double)getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing()));
    rightMotorGroup.move(-speed);
    leftMotorGroup.move(-speed);
}

void Transport::stop() {
    rightMotorGroup.brake();
    leftMotorGroup.brake();
}

void Transport::runTransport() {
    while (true) {
        bool inToggleLastState = inToggle.getCurrentState();
        bool outToggleLastState = outToggle.getCurrentState();
        inToggle.update();
        outToggle.update();
        if (inToggle.getCurrentState() && outToggle.getCurrentState()) {
            if (inToggleLastState) {
                inToggle.setCurrentState(false);
                moveOut();
            } else {
                outToggle.setCurrentState(false);
                moveIn();
            }
        }
        else if (inToggle.getCurrentState()) {
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
