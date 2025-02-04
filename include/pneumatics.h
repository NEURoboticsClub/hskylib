#ifndef PNEUMATICS
#define PNEUMATICS

#include "api.h"
#include "toggle.h"

class Pneumatics {
private:
    pros::Controller ctrl;
    pros::controller_digital_e_t extendButton;
    pros::controller_digital_e_t retractButton;
    pros::adi::DigitalOut piston;

    // main function
    void startPneumatics();

public:
    Pneumatics(char pistonPort,
        pros::controller_digital_e_t extendButton,
        pros::controller_digital_e_t retractButton,
        pros::Controller& ctrl);

    // initialize and start the task
    void initialize();
    void extendPiston();
    void retractPiston();
};

#endif
