#ifndef PNEUMATICS
#define PNEUMATICS

#include "api.h"

template <uint8_t n>
class Pneumatics {
private:
    pros::Controller ctrl;
    pros::controller_digital_e_t buttons[n];
    pros::ADIDigitalOut pistons[n];

    // main function
    void startPneumatics();

public:
    Pneumatics(char pistonPorts[n],
        pros::controller_digital_e_t buttons[n],
        pros::Controller& ctrl);

    // initialize and start the task
    void initialize();
    void activatePiston(uint8_t pistonId);
    void deactivatePiston(uint8_t pistonId);
};

#endif
