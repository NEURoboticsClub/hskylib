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
        PIDController pidCtrl;
        pros::controller_digital_e_t easeButton;
        pros::controller_digital_e_t armedButton;
        pros::controller_digital_e_t fireButton;
        pros::Rotation rotSensor;
        uint32_t setPoint;
        uint32_t easeSetPoint;
        uint32_t armedSetPoint;
        uint32_t fireSetPoint;

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
            pros::controller_digital_e_t easeButton,
            pros::controller_digital_e_t armedButton,
            pros::controller_digital_e_t fireButton,
            double motorDutyCycle,
            double kP,
            double kI,
            double kD,
            uint32_t easeSetPoint,
            uint32_t armedSetPoint,
            uint32_t fireSetPoint);

        // initialize and start the task
        void initialize();
        void moveUp();
        void moveDown();
        void stop();
};

#endif
