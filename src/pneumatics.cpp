#include "pneumatics.h"

// constructor
template <uint8_t n> Pneumatics<n>::Pneumatics(char pistonPorts[n],
    pros::controller_digital_e_t buttons[n],
    pros::Controller& ctrl)
        : ctrl(ctrl), buttons(buttons) {
        for (uint8_t i = 0; i < n; i++) {
            pistons[i] = pros::ADIDigitalOut(pistonPorts[i]);
        }
}

template <uint8_t n> void Pneumatics<n>::startPneumatics() {
    while (true) {
        for (uint8_t i = 0; i < n; i++) {
            if (ctrl.get_digital(buttons[i])) {
                activatePiston(i);
                printf("activating piston %d\n", i);
            } else {
                deactivatePiston(i);
                printf("deactivating piston %d\n", i);
            }
        }
        pros::delay(20);
    }
}

template <uint8_t n> void Pneumatics<n>::activatePiston(uint8_t pistonId) {
    pistons[pistonId].set_value(true);
}

template <uint8_t n> void Pneumatics<n>::deactivatePiston(uint8_t pistonId) {
    pistons[pistonId].set_value(false);
}

template <uint8_t n> void Pneumatics<n>::initialize() {
    pros::Task task([this] { startPneumatics(); });
}
