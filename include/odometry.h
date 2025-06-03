#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "api.h"
#include "pose.h"

/**
 * Represents odometry for a robot. Tracks and updates the robot's current position
 * based on integrated encoder, odometry pod, and/or IMU data.
 */
class Odometry // TODO: add mutex for pose (and encoders, because reset?)
{
    public:
        explicit Odometry();
        // Start the odometry task
        void init();
        // Reset the odometry object/task
        virtual void reset();
        // Get the robot's current position
        void getPose(Pose* pose);
        // Manually set the robot's current position
        void setPose(Pose* newPose);

    protected:
        // The robot's current position
        Pose* currentPose;
        // Update the robot's current position based on the latest odometry data
        virtual void updatePose();
        // Odometry main function
        void runOdometry();
};

#endif
