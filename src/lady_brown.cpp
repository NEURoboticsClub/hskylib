#include "lady_brown.h"
#include "utils.h"

// constructor
LadyBrown::LadyBrown(uint8_t armMotorPort,
    pros::Controller& ctrl,
    pros::motor_brake_mode_e brakeMode,
    pros::motor_gearset_e gearset,
    pros::controller_digital_e_t upButton,
    pros::controller_digital_e_t downButton,
    double motorDutyCycle)
        : ctrl(ctrl), upButton(upButton), downButton(downButton), motorDutyCycle(motorDutyCycle) {
            pros::Motor motor(armMotorPort);
            armMotor = &motor;
            armMotor->set_brake_mode(brakeMode);
            armMotor->set_gearing(gearset);
}

void LadyBrown::moveUp() {
    int speed = (motorDutyCycle * (double)getInputExtremeForGearset((pros::motor_gearset_e) armMotor->get_gearing()));
    armMotor->move(speed);
}

void LadyBrown::moveDown() {
    int speed = (motorDutyCycle * (double)getInputExtremeForGearset((pros::motor_gearset_e) armMotor->get_gearing()));
    armMotor->move(-speed);
}

void LadyBrown::stop() {
    armMotor->brake();
}

void LadyBrown::runLadyBrown() {
    while (true) {
        if (ctrl.get_digital(upButton)) {
            moveUp();
            printf("moving up\n");
        } else if (ctrl.get_digital(downButton)) {
            moveDown();
            printf("moving down\n");
        } else {
            stop();
            printf("stopping\n");
        }
        pros::delay(20);
    }
}

void LadyBrown::initialize() {
    pros::Task task([this] { runLadyBrown(); });
}
