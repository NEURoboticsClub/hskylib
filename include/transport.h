#ifndef TRANSPORT
#define TRANSPORT

#include "api.h"
#include "robot_config.h"
#include "toggle.h"

/**
 * A mechanism for transporting game pieces forward and backward within the
 * robot (i.e. intaking and extaking). A Transport is assigned two buttons: an
 * in button and an out button. Pressing either button when the Transport is not
 * in the indicated state (in or out) will cause the Transport to take on the
 * indicated state. Pressing either button when the Transport is in the
 * indicated state will cause it to stop.
 */
class Transport {
  public:
	Transport(TransportConfig config, pros::Controller &ctrl);

	// Initialize and start the task
	void initialize();
	// Set the Transport to an intaking state
	void moveIn();
	// Set the Transport to an extaking state
	void moveOut();
	// Stop the Transport
	void stop();

  private:
	pros::MotorGroup motors;
	// Toggle assigned to track intaking
	Toggle inToggle;
	// Toggle assigned to track extaking
	Toggle outToggle;
	// Duty cycle of the motor(s), from -1.0 to 1.0
	double motorDutyCycle;
	// Is this Transport intaking?
	bool intakeIn;
	// Is this Transport extaking?
	bool intakeOut;

	// Main function
	void runTransport();
};

#endif
