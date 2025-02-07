#include "pneumatics.h"

// constructor
Pneumatics::Pneumatics(char pistonPort,
    pros::controller_digital_e_t extendButton,
    pros::controller_digital_e_t retractButton,
    pros::Controller& ctrl)
        : ctrl(ctrl), extendButton(extendButton), retractButton(retractButton), piston(pistonPort) {
}

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

void Pneumatics::extendPiston() {
    piston.set_value(true);
}

void Pneumatics::retractPiston() {
    piston.set_value(false);
}

void Pneumatics::initialize() {
    pros::Task task([this] { startPneumatics(); }, "pneumatics");
}
