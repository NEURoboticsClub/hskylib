#ifndef PNEUMATICS
#define PNEUMATICS

#include "api.h"
#include "toggle.h"
#include "robot_config.h"

// A pneumatic component.
class Pneumatics {
    private:
        pros::Controller ctrl;
        pros::controller_digital_e_t extendButton;
        pros::controller_digital_e_t retractButton;
        pros::adi::DigitalOut piston;

        // Main function
        void startPneumatics();

    public:
        Pneumatics(PneumaticsConfig config,
            pros::Controller& ctrl);

        // Initialize and start the task
        void initialize();
        void extendPiston();
        void retractPiston();
};

#endif
