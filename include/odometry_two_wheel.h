#ifndef ODOMETRY_TWO_WHEEL_H
#define ODOMETRY_TWO_WHEEL_H

#include "api.h"
#include "odometry.h"

/**
 * Odometry using two odometry pods: left and right.
 */
class TwoWheelOdometry : public Odometry {
  public:
	// TODO: update to take a configuration instead of all these arguments
	TwoWheelOdometry(int8_t leftEncoderPort, int8_t rightEncoderPort,
					 double dW);
	void reset() override;

  protected:
	void updatePose() override;

  private:
	// Rotation sensors
	pros::Rotation leftEncoder;
	pros::Rotation rightEncoder;

	// Internal tracking of past sensor values for delta calculation
	int32_t leftEncoderLastPos;
	int32_t rightEncoderLastPos;

	// Drivebase width (center of the left wheels to center of the right wheels)
	double dW;
};

#endif
