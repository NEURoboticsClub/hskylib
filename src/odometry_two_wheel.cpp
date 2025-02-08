#include "odometry_two_wheel.h"

TwoWheelOdometry::TwoWheelOdometry(int8_t leftEncoderPort, int8_t rightEncoderPort, double dW)
    : Odometry(), dW(dW), leftEncoder(leftEncoderPort), rightEncoder(rightEncoderPort) {
    leftEncoder.reset_position();
    rightEncoder.reset_position();
    leftEncoderLastPos = 0;
    rightEncoderLastPos = 0;
}

void TwoWheelOdometry::reset() {
    Odometry::reset();

    leftEncoder.reset_position();
    rightEncoder.reset_position();
    leftEncoderLastPos = 0;
    rightEncoderLastPos = 0;
}

void TwoWheelOdometry::updatePose() {
    // math based off of: https://medium.com/@nahmed3536/wheel-odometry-model-for-differential-drive-robotics-91b85a012299
    int32_t leftEncoderNewPos = leftEncoder.get_position();
    int32_t rightEncoderNewPos = rightEncoder.get_position();
    double dL = (((double) leftEncoderNewPos - (double) leftEncoderLastPos) / 36000.0) * 6.28318;
    double dR = (((double) rightEncoderNewPos - (double) rightEncoderLastPos) / 36000.0) * 6.28318;
    double d = (dL + dR) / 2.0;
    double deltaThetaRad = (dR - dL) / (2.0 * dW);

    double x = currentPose->x + (d * (double)cos(currentPose->theta + (deltaThetaRad / 2.0)));
    double y = currentPose->y + (d * (double)sin(currentPose->theta + (deltaThetaRad / 2.0)));
    double theta = currentPose->theta + deltaThetaRad;

    currentPose->x = x;
    currentPose->y = y;
    currentPose->theta = theta;

    leftEncoderLastPos = leftEncoderNewPos;
    rightEncoderLastPos = rightEncoderNewPos;
}