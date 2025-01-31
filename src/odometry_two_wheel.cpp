#include "odometry_two_wheel.h"

OdometryTwoWheel::OdometryTwoWheel(uint8_t leftEncoderPort, uint8_t rightEncoderPort, double dW)
    : OdometryBase(), dW(dW) {
    pros::Rotation left(leftEncoderPort);
    pros::Rotation right(rightEncoderPort);
    leftEncoder = &left;
    rightEncoder = &right;
    leftEncoder->reset_position();
    rightEncoder->reset_position();
    leftEncoderLastPos = 0;
    rightEncoderLastPos = 0;
}

void OdometryTwoWheel::reset() {
    OdometryBase::reset();

    leftEncoder->reset_position();
    rightEncoder->reset_position();
    leftEncoderLastPos = 0;
    rightEncoderLastPos = 0;
}

void OdometryTwoWheel::updatePosition() {
    // math based off of: https://medium.com/@nahmed3536/wheel-odometry-model-for-differential-drive-robotics-91b85a012299
    uint16_t leftEncoderNewPos = leftEncoder->get_position();
    uint16_t rightEncoderNewPos = rightEncoder->get_position();
    double dL = ((double) leftEncoderNewPos - (double) leftEncoderLastPos) * 6.28318;
    double dR = ((double) rightEncoderNewPos - (double) rightEncoderLastPos) * 6.28318;
    double d = (dL + dR) / 2.0;
    double deltaThetaRad = (dR - dL) / (2.0 * dW);

    double x = *currentPosition[0] + (d * (double)cos(*currentPosition[2] + (deltaThetaRad / 2.0)));
    double y = *currentPosition[1] + (d * (double)sin(*currentPosition[2] + (deltaThetaRad / 2.0)));
    double theta = *currentPosition[2] + deltaThetaRad;

    *currentPosition[0] = x;
    *currentPosition[1] = y;
    *currentPosition[2] = theta;

    leftEncoderLastPos = leftEncoderNewPos;
    rightEncoderLastPos = rightEncoderNewPos;
}