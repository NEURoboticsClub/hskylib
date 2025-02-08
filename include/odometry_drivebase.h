#ifndef ODOMETRY_DRIVEBASE_H
#define ODOMETRY_DRIVEBASE_H

#include "api.h"
#include "odometry.h"

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
        pros::MotorGroup leftMotorGroup;
        pros::MotorGroup rightMotorGroup;
        double leftMotorGroupLastPos;
        double rightMotorGroupLastPos;
        double dW;
};

#endif
