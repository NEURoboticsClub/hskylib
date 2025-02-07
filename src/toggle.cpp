#include "toggle.h"

// constructor
Toggle::Toggle(pros::Controller& ctrl,
    pros::controller_digital_e_t button)
        : ctrl(ctrl), button(button) {
            previousButtonState = false;
            currentOnState = false;
}

void Toggle::update() {
    bool input = ctrl.get_digital(button);
    if(input != previousButtonState){
        if(input){
            currentOnState = !currentOnState;
        }
        previousButtonState = input;
    }
}

bool Toggle::getCurrentState() {
    return currentOnState;
}

void Toggle::setCurrentState(bool state) {
    currentOnState = state;
}

void Toggle::reset() {
    previousButtonState = false;
    currentOnState = false;
}
