#ifndef ODOMETRY_BASE_H
#define ODOMETRY_BASE_H

#include "api.h"

class OdometryBase
{
    public:
        OdometryBase();
        virtual void init();
        virtual void reset();
        virtual void getPosition(double* pos[3]);
        virtual void setPosition(double* pos[3]);

    protected:
        double* currentPosition[3];
        virtual void updatePosition() = 0;
};

#endif
