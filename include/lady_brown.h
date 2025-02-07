#ifndef LADY_BROWN
#define LADY_BROWN

#include "api.h"
#include "toggle.h"
#include "pid_controller.h"

class LadyBrown {
    private:
        pros::Motor armMotor;
        pros::Controller ctrl;
        pros::controller_digital_e_t upButton;
        pros::controller_digital_e_t downButton;
        double motorDutyCycle;
        PIDController<double>* pidCtrl;
        pros::Rotation rotSensor;
        int32_t setPoint;
        int32_t easeSetPoint;
        int32_t armedSetPoint;
        int32_t fireSetPoint;
        Toggle macroForwardToggle;
        Toggle macroBackToggle;

        // main function
        void runLadyBrown();

    public:
        LadyBrown(int8_t armMotorPort,
            int8_t sensorPort,
            pros::Controller& ctrl,
            pros::motor_brake_mode_e brakeMode,
            pros::motor_gearset_e gearset,
            pros::controller_digital_e_t upButton,
            pros::controller_digital_e_t downButton,
            pros::controller_digital_e_t macroForwardButton,
            pros::controller_digital_e_t macroBackButton,
            double motorDutyCycle,
            double kP,
            double kI,
            double kD,
            int32_t easeSetPoint,
            int32_t armedSetPoint,
            int32_t fireSetPoint);
        
        ~LadyBrown();

        // initialize and start the task
        void initialize();
        void stop();
};

#endif
