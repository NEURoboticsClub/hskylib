#ifndef LADY_BROWN
#define LADY_BROWN

#include "api.h"
#include "pid_controller.h"
#include "robot_config.h"
#include "toggle.h"

class LadyBrown {
  public:
	LadyBrown(LadyBrownConfig config, pros::Controller &ctrl);

	~LadyBrown();

	// initialize and start the task
	void initialize();
	void stop();

  private:
	pros::Motor armMotor;
	pros::Controller ctrl;
	pros::controller_digital_e_t upButton;
	pros::controller_digital_e_t downButton;
	double motorDutyCycle;
	PIDController<double> *pidCtrl;
	pros::Rotation rotSensor;
	int32_t setPoint;
	int32_t easeSetPoint;
	int32_t armedSetPoint;
	int32_t fireSetPoint;
	Toggle macroForwardToggle;
	Toggle macroBackToggle;

	// main function
	void runLadyBrown();
};

#endif
