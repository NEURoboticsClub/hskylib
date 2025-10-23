#include "odometry_two_wheel_imu.h"

TwoWheelImuOdometry::TwoWheelImuOdometry(
    int8_t leftEncoderPort, int8_t rightEncoderPort,
    int8_t imu1Port, int8_t imu2Port, double dW, double wheelAngleDeg)
  : imu1(imu1Port),
    imu2(imu2Port),
    leftEncoder(leftEncoderPort),
    rightEncoder(rightEncoderPort),
    dW(dW),
    leftEncoderLastPos(0),
    rightEncoderLastPos(0),
    wheelAngleDeg(wheelAngleDeg) {}

void TwoWheelImuOdometry::reset() {
	imu1.reset();
    imu2.reset();
    while (imu1.is_calibrating() || imu2.is_calibrating()) pros::delay(10);
    leftEncoder.reset_position();
    rightEncoder.reset_position();
    leftEncoderLastPos = 0;
    rightEncoderLastPos = 0;
}

void TwoWheelImuOdometry::updatePose() {
	int32_t leftEncoderNewPos = leftEncoder.get_position();
	int32_t rightEncoderNewPos = rightEncoder.get_position();
	double dL =
		(((double)leftEncoderNewPos - (double)leftEncoderLastPos) / 36000.0) *
		6.28318;
	double dR =
		(((double)rightEncoderNewPos - (double)rightEncoderLastPos) / 36000.0) *
		6.28318;
    
    double thetaDeg = (imu1.get_rotation() + imu2.get_rotation()) / 2.0;
    double thetaRad = thetaDeg *(M_PI / 180);

    // Convert wheel readings into robot motion (decompose dl and dr, average results)
    double angleRad = wheelAngleDeg * (M_PI / 180.0);
    double dx_robot = ((dL + dR) / 2.0) * cos(angleRad);
    double dy_robot = ((dL - dR) / 2.0) * sin(angleRad);

    // Rotate into field based on IMU heading
    double dx_field = dx_robot * cos(thetaRad) - dy_robot * sin(thetaRad);
    double dy_field = dx_robot * sin(thetaRad) + dy_robot * cos(thetaRad);

	currentPose->x += dx_field;
	currentPose->y += dy_field;
	currentPose->theta = thetaRad;

	leftEncoderLastPos = leftEncoderNewPos;
	rightEncoderLastPos = rightEncoderNewPos;
}