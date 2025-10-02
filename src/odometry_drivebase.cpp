#include "odometry_drivebase.h"

DrivebaseOdometry::DrivebaseOdometry(std::vector<int8_t> leftMotors,
									 std::vector<int8_t> rightMotors,
									 pros::motor_gearset_e gearset, double dW)
	: Odometry(),
	  dW(dW),
	  leftMotorGroup(leftMotors),
	  rightMotorGroup(rightMotors) {
	leftMotorGroup.set_gearing_all(gearset);
	rightMotorGroup.set_gearing_all(gearset);
	leftMotorGroup.set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
	rightMotorGroup.set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
	leftMotorGroup.tare_position_all();
	rightMotorGroup.tare_position_all();
	leftMotorGroupLastPos = 0;
	rightMotorGroupLastPos = 0;
}

void DrivebaseOdometry::reset() {
	Odometry::reset();

	leftMotorGroup.set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
	rightMotorGroup.set_encoder_units_all(pros::E_MOTOR_ENCODER_DEGREES);
	leftMotorGroup.tare_position_all();
	rightMotorGroup.tare_position_all();
	leftMotorGroupLastPos = 0;
	rightMotorGroupLastPos = 0;
}

void DrivebaseOdometry::updatePose() {
	// math based off of:
	// https://medium.com/@nahmed3536/wheel-odometry-model-for-differential-drive-robotics-91b85a012299
	double leftMotorGroupNewPos = static_cast<double>(leftMotorGroup.get_position(0));
	double rightMotorGroupNewPos = static_cast<double>(rightMotorGroup.get_position(0));
	double dL =
		static_cast<double>(((leftMotorGroupNewPos - (double)leftMotorGroupLastPos) / 360.0) *
		(39.0 / 57.0) * 10.205);
	double dR =
		static_cast<double>(((rightMotorGroupNewPos - (double)rightMotorGroupLastPos) / 360.0) *
		(39.0 / 57.0) * 10.205);
	double d = static_cast<double>((dL + dR) / 2.0);
	double deltaThetaRad = static_cast<double>((dR - dL) / (2.0 * dW));

	printf("Calculating...");

	double x = static_cast<double>(currentPose->x +
			   (d * (double)cos(currentPose->theta + (deltaThetaRad / 2.0))));
	double y = static_cast<double>(currentPose->y +
			   (d * (double)sin(currentPose->theta + (deltaThetaRad / 2.0))));
	double theta = static_cast<double>(currentPose->theta + deltaThetaRad);

	currentPose->x = x;
	currentPose->y = y;
	currentPose->theta = theta;

	leftMotorGroupLastPos = leftMotorGroupNewPos;
	rightMotorGroupLastPos = rightMotorGroupNewPos;
}