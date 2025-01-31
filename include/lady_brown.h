#ifndef LADY_BROWN
#define LADY_BROWN

#include "api.h"
#include "toggle.h"

class LadyBrown {
private:
    pros::Motor* armMotor;
    pros::Controller ctrl;
    pros::controller_digital_e_t upButton;
    pros::controller_digital_e_t downButton;
    double motorDutyCycle;

    // main function
    void runLadyBrown();

public:
    LadyBrown(uint8_t armMotorPort,
        pros::Controller& ctrl,
        pros::motor_brake_mode_e brakeMode,
        pros::motor_gearset_e gearset,
        pros::controller_digital_e_t upButton,
        pros::controller_digital_e_t downButton,
        double motorDutyCycle);

    // initialize and start the task
    void initialize();
    void moveUp();
    void moveDown();
    void stop();
};

#endif
