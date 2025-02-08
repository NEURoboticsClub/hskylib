#include "odometry_drivebase.h"

DrivebaseOdometry::DrivebaseOdometry(std::vector<int8_t> leftMotors,
    std::vector<int8_t> rightMotors,
    pros::motor_gearset_e gearset,
    double dW)
        : Odometry(), dW(dW), leftMotorGroup(leftMotors), rightMotorGroup(rightMotors) {
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
    // math based off of: https://medium.com/@nahmed3536/wheel-odometry-model-for-differential-drive-robotics-91b85a012299
    double leftMotorGroupNewPos = leftMotorGroup.get_position(0);
    double rightMotorGroupNewPos = rightMotorGroup.get_position(0);
    double dL = ((leftMotorGroupNewPos - (double) leftMotorGroupLastPos) / 360.0) * (57.0 / 39.0) * 10.205;
    double dR = ((rightMotorGroupNewPos - (double) rightMotorGroupLastPos) / 360.0) * (57.0 / 39.0) * 10.205;
    double d = (dL + dR) / 2.0;
    double deltaThetaRad = (dR - dL) / (2.0 * dW);

    // printf("Calculating...");

    double x = currentPose->x + (d * (double)cos(currentPose->theta + (deltaThetaRad / 2.0)));
    double y = currentPose->y + (d * (double)sin(currentPose->theta + (deltaThetaRad / 2.0)));
    double theta = currentPose->theta + deltaThetaRad;

    currentPose->x = x;
    currentPose->y = y;
    currentPose->theta = theta;

    leftMotorGroupLastPos = leftMotorGroupNewPos;
    rightMotorGroupLastPos = rightMotorGroupNewPos;
}