#ifndef LADY_BROWN
#define LADY_BROWN

#include "api.h"

class LadyBrown {
private:
    pros::MotorGroup leftMotorGroup = {};
    pros::MotorGroup rightMotorGroup = {};
    double motorDutyCycle;

    // main function
    void runTransport();

public:
    Transport(pros::MotorGroup& leftMotors,
        pros::MotorGroup& rightMotors,
        pros::Controller& ctrl,
        pros::motor_brake_mode_e brakeMode,
        pros::motor_gearset_e gearset,
        pros::controller_digital_e_t inButton,
        pros::controller_digital_e_t outButton,
        double motorDutyCycle);

    // initialize and start the task
    void initialize();
    void moveIn();
    void moveOut();
    void stop();
};

#endif
