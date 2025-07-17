#include "pneumatics.h"

// constructor
Pneumatics::Pneumatics(PneumaticsConfig config, pros::Controller &ctrl)
	: ctrl(ctrl),
	  extendButton(config.extendButton),
	  retractButton(config.retractButton),
	  piston(config.port) {}

void Pneumatics::startPneumatics() {
	while (true) {
		if (ctrl.get_digital(extendButton)) {
			extendPiston();
			printf("extending piston");
		} else if (ctrl.get_digital(retractButton)) {
			retractPiston();
			printf("deactivating piston");
		}
		pros::delay(20);
	}
}

void Pneumatics::extendPiston() { piston.set_value(true); }

void Pneumatics::retractPiston() { piston.set_value(false); }

void Pneumatics::initialize() {
	pros::Task task([this] { startPneumatics(); }, "pneumatics");
}
