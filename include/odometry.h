#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "api.h"
#include "pose.h"

class Odometry // TODO: add mutex for pose (and encoders, because reset?)
{
    public:
        explicit Odometry();
        void init();
        virtual void reset();
        Pose getPose();
        void setPose(Pose newPose);

    protected:
        Pose currentPose;
        virtual void updatePose();
        void runOdometry();
};

#endif
