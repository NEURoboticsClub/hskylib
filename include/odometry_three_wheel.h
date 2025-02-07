#ifndef ODOMETRY_THREE_WHEEL_H
#define ODOMETRY_THREE_WHEEL_H

#include "api.h"
#include "odometry.h"

class OdometryThreeWheel: public Odometry
{
    public:
        OdometryThreeWheel(int8_t leftEncoderPort, int8_t rightEncoderPort, int8_t centerEncoderPort, double sL, double sR, double sS);
        void reset() override;
    
    protected:
        void updatePose() override;

    private:
        pros::Rotation leftEncoder;
        pros::Rotation rightEncoder;
        pros::Rotation centerEncoder;
        uint32_t leftEncoderLastPos;
        uint32_t rightEncoderLastPos;
        uint32_t centerEncoderLastPos;
        double sL;
        double sR;
        double sS;
};

#endif
