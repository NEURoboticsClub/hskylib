#ifndef TRANSPORT
#define TRANSPORT

#include "api.h"
#include "robot_config.h"
#include "toggle.h"

class Transport {
  public:
	Transport(TransportConfig config, pros::Controller &ctrl);

	// Initialize and start the task
	void initialize();
	void moveIn();
	void moveOut();
	void stop();

  private:
	pros::MotorGroup motors;
	Toggle inToggle;
	Toggle outToggle;
	double motorDutyCycle;
	bool intakeIn;
	bool intakeOut;

	// Main function
	void runTransport();
};

#endif
