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
    pros::controller_digital_e_t macroForwardButton,
    pros::controller_digital_e_t macroBackButton,
    double motorDutyCycle,
    double kP,
    double kI,
    double kD,
    int32_t easeSetPoint,
    int32_t armedSetPoint,
    int32_t fireSetPoint)
        : ctrl(ctrl),
        upButton(upButton),
        downButton(downButton),
        macroForwardToggle(ctrl, macroForwardButton),
        macroBackToggle(ctrl, macroBackButton),
        motorDutyCycle(motorDutyCycle),
        armMotor(armMotorPort),
        rotSensor(sensorPort),
        easeSetPoint(easeSetPoint),
        armedSetPoint(armedSetPoint),
        fireSetPoint(fireSetPoint) {
            armMotor.set_brake_mode(brakeMode);
            armMotor.set_gearing(gearset);
            setPoint = 0;
            rotSensor.set_reversed(true);
            rotSensor.reset_position();
            pidCtrl = new PIDController<double>(kP,kI,kD);
}

LadyBrown::~LadyBrown() {
    delete pidCtrl;
}

void LadyBrown::stop() {
    armMotor.brake();
}

void LadyBrown::runLadyBrown() {
    while (true) {
        macroForwardToggle.update();
        macroBackToggle.update();
        if (ctrl.get_digital(upButton)) {
            setPoint += 600;
        } else if (ctrl.get_digital(downButton)) {
            setPoint -= 600;
        } else {
            if (macroForwardToggle.getCurrentState()) {
                if (setPoint == armedSetPoint) {
                    setPoint = fireSetPoint;
                } else if (setPoint == fireSetPoint) {
                    setPoint = easeSetPoint;
                } else {
                    setPoint = armedSetPoint;
                }
                macroForwardToggle.setCurrentState(false);
            } else if (macroBackToggle.getCurrentState()) {
                if (setPoint == armedSetPoint) {
                    setPoint = easeSetPoint;
                } else if (setPoint == easeSetPoint) {
                    setPoint = fireSetPoint;
                } else {
                    setPoint = armedSetPoint;
                }
                macroBackToggle.setCurrentState(false);
            }
        }
        int16_t maxMotorMag = getInputExtremeForGearset((pros::motor_gearset_e)armMotor.get_gearing());
        printf("setpoint: %d\n", setPoint);
        double pidVal = std::clamp((int16_t)pidCtrl->compute((double)setPoint, (double)rotSensor.get_position()), (int16_t)(maxMotorMag * -1), maxMotorMag);
        armMotor.move(pidVal);
        pros::delay(20);
    }
}

void LadyBrown::initialize() {
    pros::Task task([this] { runLadyBrown(); }, "lady brown");
}
