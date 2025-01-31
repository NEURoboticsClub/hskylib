#ifndef ODOMETRY_THREE_WHEEL_H
#define ODOMETRY_THREE_WHEEL_H

#include "api.h"
#include "odometry_base.h"

class OdometryThreeWheel: public OdometryBase
{
    public:
        OdometryThreeWheel(uint8_t leftEncoderPort, uint8_t rightEncoderPort, uint8_t centerEncoderPort, double sL, double sR, double sS);
        void reset();
    
    protected:
        void updatePosition();

    private:
        pros::Rotation* leftEncoder;
        pros::Rotation* rightEncoder;
        pros::Rotation* centerEncoder;
        uint16_t leftEncoderLastPos;
        uint16_t rightEncoderLastPos;
        uint16_t centerEncoderLastPos;
        double sL;
        double sR;
        double sS;
};

#endif
