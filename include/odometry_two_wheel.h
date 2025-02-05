#ifndef ODOMETRY_TWO_WHEEL_H
#define ODOMETRY_TWO_WHEEL_H

#include "api.h"
#include "odometry.h"

class TwoWheelOdometry : public Odometry
{
    public:
        TwoWheelOdometry(int8_t leftEncoderPort, int8_t rightEncoderPort, double dW);
        void reset() override;

    protected:
        void updatePose() override;

    private:
        pros::Rotation leftEncoder;
        pros::Rotation rightEncoder;
        uint32_t leftEncoderLastPos;
        uint32_t rightEncoderLastPos;
        double dW;
};

#endif
