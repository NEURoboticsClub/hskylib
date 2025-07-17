#ifndef ODOMETRY_THREE_WHEEL_H
#define ODOMETRY_THREE_WHEEL_H

#include "api.h"
#include "odometry.h"

/**
 * Odometry using three odometry pods: left, right, and middle.
 */
class OdometryThreeWheel : public Odometry {
  public:
	// TODO: update to take a configuration instead of all these arguments
	OdometryThreeWheel(int8_t leftEncoderPort, int8_t rightEncoderPort,
					   int8_t centerEncoderPort, double sL, double sR,
					   double sS);
	void reset() override;

  protected:
	void updatePose() override;

  private:
	// Rotation sensors
	pros::Rotation leftEncoder;
	pros::Rotation rightEncoder;
	pros::Rotation centerEncoder;

	// Internal tracking of past sensor values for delta calculation
	uint32_t leftEncoderLastPos;
	uint32_t rightEncoderLastPos;
	uint32_t centerEncoderLastPos;

	// Distance from center of rotation to left, right, and center
	// odometry pods, respectively
	double sL;
	double sR;
	double sS;
};

#endif
