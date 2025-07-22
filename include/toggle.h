#ifndef TOGGLE_H
#define TOGGLE_H

#include "api.h"

/**
 * A boolean toggle. Implements logic such that each time the assigned button is
 * pressed, the value of the Toggle is negated.
 */
class Toggle {
  public:
	Toggle(pros::Controller &ctrl, pros::controller_digital_e_t button);
	void reset();
	bool getCurrentState();
	void setCurrentState(bool state);
	// Updates the value of the toggle based on the current state of the
	// assigned button
	void update();

  private:
	pros::Controller ctrl;
	// The assigned button
	pros::controller_digital_e_t button;
	// The state of the assigned button on last update
	bool previousButtonState;
	// The current boolean value of this Toggle
	bool currentOnState;
};

#endif
