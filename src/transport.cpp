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
        inToggle.update();
        outToggle.update();
        printf("in state: %d; out state: %d\n", inToggle.getCurrentState(), outToggle.getCurrentState());
        if (inToggle.getCurrentState()) {
            outToggle.setCurrentState(false);
            moveIn();
            printf("moving in\n");
        } else if (outToggle.getCurrentState()) {
            inToggle.setCurrentState(false);
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
