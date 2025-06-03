#ifndef ODOMETRY_DRIVEBASE_H
#define ODOMETRY_DRIVEBASE_H

#include "api.h"
#include "odometry.h"

/**
 * Odometry using the integrated encoders in the drivebase. Assumes tank drive.
 */
class DrivebaseOdometry : public Odometry
{
    public:
        DrivebaseOdometry(std::vector<int8_t> leftMotors,
            std::vector<int8_t> rightMotors,
            pros::motor_gearset_e gearset,
            double dW);
        void reset() override;

    protected:
        void updatePose() override;

    private:
        // Drivebase motors, from which to fetch encoder data
        pros::MotorGroup leftMotorGroup;
        pros::MotorGroup rightMotorGroup;

        // Internal tracking of past encoder values for delta calculation
        double leftMotorGroupLastPos;
        double rightMotorGroupLastPos;

        // Drivebase width (center of the left wheels to center of the right wheels)
        double dW;
};

#endif
