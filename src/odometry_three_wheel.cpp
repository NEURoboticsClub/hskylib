#include "odometry_three_wheel.h"

OdometryThreeWheel::OdometryThreeWheel(uint8_t leftEncoderPort, uint8_t rightEncoderPort, uint8_t centerEncoderPort, double sL, double sR, double sS)
    : OdometryBase(), sL(sL), sR(sR), sS(sS) {
    pros::Rotation left(leftEncoderPort);
    pros::Rotation right(rightEncoderPort);
    pros::Rotation center(centerEncoderPort);
    leftEncoder = &left;
    rightEncoder = &right;
    centerEncoder = &center;
    leftEncoder->reset_position();
    rightEncoder->reset_position();
    centerEncoder->reset_position();
    leftEncoderLastPos = 0;
    rightEncoderLastPos = 0;
    centerEncoderLastPos = 0;
}

void OdometryThreeWheel::reset() {
    OdometryBase::reset();

    leftEncoder->reset_position();
    rightEncoder->reset_position();
    centerEncoder->reset_position();
    leftEncoderLastPos = 0;
    rightEncoderLastPos = 0;
    centerEncoderLastPos = 0;
}

void OdometryThreeWheel::updatePosition() {
    uint16_t leftEncoderNewPos = leftEncoder->get_position();
    uint16_t rightEncoderNewPos = rightEncoder->get_position();
    uint16_t centerEncoderNewPos = centerEncoder->get_position();
    double dL = ((double) leftEncoderNewPos - (double) leftEncoderLastPos) * 6.28318;
    double dR = ((double) rightEncoderNewPos - (double) rightEncoderLastPos) * 6.28318;
    double dC = ((double) centerEncoderNewPos - (double) centerEncoderLastPos) * 6.28318;
    double deltaThetaRad = (dL - dR) / (sL + sR);

    double localOffsetX = (2.0 * sin(deltaThetaRad / 2.0) * (dC / deltaThetaRad) + sS);
    double localOffsetY = (dR / deltaThetaRad) + sR;
    double thetaM = *currentPosition[2] + (deltaThetaRad / 2.0);

    double dX = (localOffsetX * cos(thetaM)) - (localOffsetY * sin(thetaM));
    double dY = (localOffsetX * sin(thetaM)) + (localOffsetY * cos(thetaM));

    double x = *currentPosition[0] + dX;
    double y = *currentPosition[1] + dY;
    double theta = *currentPosition[2] + deltaThetaRad;

    *currentPosition[0] = x;
    *currentPosition[1] = y;
    *currentPosition[2] = theta;

    leftEncoderLastPos = leftEncoderNewPos;
    rightEncoderLastPos = rightEncoderNewPos;
    centerEncoderLastPos = centerEncoderNewPos;
}