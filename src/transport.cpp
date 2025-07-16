#include "transport.h"

#include "utils.h"

// constructor
Transport::Transport(TransportConfig config, pros::Controller &ctrl)
	: inToggle(ctrl, config.inButton),
	  outToggle(ctrl, config.outButton),
	  motorDutyCycle(config.dutyCycle),
	  motors(config.motors) {
	motors.set_brake_mode_all(config.brakeMode);
	motors.set_gearing_all(config.gearset);
	intakeIn = false;
	intakeOut = false;
}

void Transport::moveIn() {
	int speed =
		(motorDutyCycle * (double)getInputExtremeForGearset(
							  (pros::motor_gearset_e)motors.get_gearing()));
	motors.move(speed);
}

void Transport::moveOut() {
	int speed =
		(motorDutyCycle * (double)getInputExtremeForGearset(
							  (pros::motor_gearset_e)motors.get_gearing()));
	motors.move(-speed);
}

void Transport::stop() { motors.brake(); }

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
		} else if (inToggle.getCurrentState()) {
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
