#ifndef ODOMETRY_TWO_POD_TWO_IMU_H
#define ODOMETRY_TWO_POD_TWO_IMU_H

#include "api.h"
#include "odometry.h"

/**
 * Odometry using two odometry pods: left and right, and two IMU
 */
class TwoWheelImuOdometry : public Odometry {
  public:
	TwoWheelImuOdometry(int8_t leftEncoderPort, int8_t rightEncoderPort,
        int8_t imu1Port, int8_t imu2Port, double dW, double wheelAngleDeg);
	void reset() override;

  protected:
	void updatePose() override;

  private:
	// IMU's
    pros::Imu imu1;
    pros::Imu imu2;

    // Rotation sensors
	pros::Rotation leftEncoder;
	pros::Rotation rightEncoder;

	// Internal tracking of past sensor values for delta calculation
	int32_t leftEncoderLastPos;
	int32_t rightEncoderLastPos;

	// Drivebase width (center of the left wheels to center of the right wheels)
	double dW;

	// Angle of the pods in degrees
	double wheelAngleDeg;
};

#endif
