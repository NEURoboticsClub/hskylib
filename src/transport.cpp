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
        printf("in state: %d; out state: %d\n", inToggle.getCurrentState(), outToggle.getCurrentState());
        if (inToggle.getCurrentState() && outToggle.getCurrentState()) {
            if (inToggleLastState) {
                inToggle.setCurrentState(false);
                moveOut();
                printf("moving out\n");
            } else {
                outToggle.setCurrentState(false);
                moveIn();
                printf("moving in\n");
            }
        }
        else if (inToggle.getCurrentState()) {
            moveIn();
            printf("moving in\n");
        } else if (outToggle.getCurrentState()) {
            moveOut();
            printf("moving out\n");
        } else {
            stop();
            printf("stopping\n");
        }
        pros::delay(20);
    }
}

void Transport::initialize() {
    pros::Task task([this] { runTransport(); });
}
