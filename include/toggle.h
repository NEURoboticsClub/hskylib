#ifndef TOGGLE_H
#define TOGGLE_H

#include "api.h"

class Toggle {
private:
    pros::Controller ctrl;
    pros::controller_digital_e_t button;
    bool previousButtonState;
    bool currentOnState;

public:
    Toggle(pros::Controller& ctrl, pros::controller_digital_e_t button);
    void reset();
    bool getCurrentState();
    void setCurrentState(bool state);
    void update();
};

#endif
