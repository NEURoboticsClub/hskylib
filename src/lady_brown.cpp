#include "lady_brown.h"
#include "utils.h"

// constructor
LadyBrown::LadyBrown(int8_t armMotorPort,
    int8_t sensorPort,
    pros::Controller& ctrl,
    pros::motor_brake_mode_e brakeMode,
    pros::motor_gearset_e gearset,
    pros::controller_digital_e_t upButton,
    pros::controller_digital_e_t downButton,
    pros::controller_digital_e_t easeButton,
    pros::controller_digital_e_t armedButton,
    pros::controller_digital_e_t fireButton,
    double motorDutyCycle,
    double kP,
    double kI,
    double kD,
    uint32_t easeSetPoint,
    uint32_t armedSetPoint,
    uint32_t fireSetPoint)
        : ctrl(ctrl),
        upButton(upButton),
        downButton(downButton),
        armedButton(armedButton),
        easeButton(easeButton),
        fireButton(fireButton),
        motorDutyCycle(motorDutyCycle),
        armMotor(armMotorPort),
        pidCtrl(kP,kI,kD),
        rotSensor(sensorPort),
        easeSetPoint(easeSetPoint),
        armedSetPoint(armedSetPoint),
        fireSetPoint(fireSetPoint) {
            armMotor.set_brake_mode(brakeMode);
            armMotor.set_gearing(gearset);
            setPoint = 0;
            rotSensor.reset_position();
}

void LadyBrown::moveUp() {
    int speed = (motorDutyCycle * (double)getInputExtremeForGearset((pros::motor_gearset_e) armMotor.get_gearing()));
    armMotor.move(speed);
}

void LadyBrown::moveDown() {
    int speed = (motorDutyCycle * (double)getInputExtremeForGearset((pros::motor_gearset_e) armMotor.get_gearing()));
    armMotor.move(-speed);
}

void LadyBrown::stop() {
    armMotor.brake();
}

void LadyBrown::runLadyBrown() {
    while (true) {
        if (ctrl.get_digital(upButton)) {
            moveUp();
        } else if (ctrl.get_digital(downButton)) {
            moveDown();
        } else {
            if (ctrl.get_digital(easeButton)) {
                setPoint = easeSetPoint;
            } else if (ctrl.get_digital(armedButton)) {
                setPoint = armedSetPoint;
            } else if (ctrl.get_digital(fireButton)) {
                setPoint = fireSetPoint;
            }
            int16_t maxMotorMag = getInputExtremeForGearset((pros::motor_gearset_e)armMotor.get_gearing());
            double pidVal = std::clamp((int16_t)pidCtrl.compute(setPoint, rotSensor.get_position()), (int16_t)(maxMotorMag * -1), maxMotorMag);
            armMotor.move(-pidVal);
        }
        pros::delay(20);
    }
}

void LadyBrown::initialize() {
    pros::Task task([this] { runLadyBrown(); }, "lady brown");
}
