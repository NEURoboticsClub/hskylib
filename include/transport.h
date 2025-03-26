#ifndef TRANSPORT
#define TRANSPORT

#include "api.h"
#include "toggle.h"
#include "robot_config.h"

class Transport {
private:
    pros::MotorGroup motors;
    Toggle inToggle;
    Toggle outToggle;
    double motorDutyCycle;
    bool intakeIn;
    bool intakeOut;

    // main function
    void runTransport();
    

public:
    Transport(TransportConfig config,
        pros::Controller& ctrl);

    // initialize and start the task
    void initialize();
    void moveIn();
    void moveOut();
    void stop();
};

#endif
