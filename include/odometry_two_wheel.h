#ifndef ODOMETRY_TWO_WHEEL_H
#define ODOMETRY_TWO_WHEEL_H

#include "api.h"
#include "odometry_base.h"

class OdometryTwoWheel: public OdometryBase
{
    public:
        OdometryTwoWheel(uint8_t leftEncoderPort, uint8_t rightEncoderPort, double dW);
        void reset();

    protected:
        void updatePosition();

    private:
        pros::Rotation* leftEncoder;
        pros::Rotation* rightEncoder;
        uint16_t leftEncoderLastPos;
        uint16_t rightEncoderLastPos;
        double dW;
};

#endif
