#include "lady_brown.h"

#include "utils.h"

// constructor
LadyBrown::LadyBrown(LadyBrownConfig config, pros::Controller &ctrl)
	: ctrl(ctrl),
	  upButton(config.upButton),
	  downButton(config.downButton),
	  macroForwardToggle(ctrl, config.macroForwardButton),
	  macroBackToggle(ctrl, config.macroBackButton),
	  motorDutyCycle(config.dutyCycle),
	  armMotor(config.armPort),
	  rotSensor(config.sensorPort),
	  easeSetPoint(config.easeSetPoint),
	  armedSetPoint(config.armedSetPoint),
	  fireSetPoint(config.fireSetPoint) {
	armMotor.set_brake_mode(config.brakeMode);
	armMotor.set_gearing(config.gearset);
	setPoint = 0;
	rotSensor.set_reversed(true);
	rotSensor.reset_position();
	pidCtrl = new PIDController<double>(config.kP, config.kI, config.kD);
}

LadyBrown::~LadyBrown() { delete pidCtrl; }

void LadyBrown::stop() { armMotor.brake(); }

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
		int16_t maxMotorMag = getInputExtremeForGearset(
			(pros::motor_gearset_e)armMotor.get_gearing());
		printf("setpoint: %d\n", setPoint);
		double pidVal =
			std::clamp((int16_t)pidCtrl->compute(
						   (double)setPoint, (double)rotSensor.get_position()),
					   (int16_t)(maxMotorMag * -1), maxMotorMag);
		armMotor.move(pidVal);
		pros::delay(20);
	}
}

void LadyBrown::initialize() {
	pros::Task task([this] { runLadyBrown(); }, "lady brown");
}
