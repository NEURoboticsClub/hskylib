#ifndef TANKDRIVE_H
#define TANKDRIVE_H

#include "api.h"
#include "utils.h"
#include "pid_controller.h"
#include "odometry_three_wheel.h"
#include "odometry_drivebase.h"
#include "odometry.h"
#include "pose.h"
#include "robot_config.h"

/**
 * A tank drive drivebase. Contains functions for both manual and
 * autonomous control.
 */
class TankDrive {
    public:
        TankDrive(DrivebaseConfig config,
            pros::Controller& ctrl);
        
        ~TankDrive();

        // initialize and start the task
        void initialize(DriveStyle driveStyle);
        
        // Autonomous movement methods
        void initAuton();
        void driveToPose(Pose* targetPose);
        void turnToHeading(double targetHeadingDegrees);
        void driveDistance(double distIn);
        void driveToPoint(double targetX, double targetY);
    private:
        pros::MotorGroup leftMotorGroup;
        pros::MotorGroup rightMotorGroup;
        pros::Controller controller;
        double speedMultiplier;
        Odometry* odom;
        Pose* setPoint = new Pose(0.0,0.0,0.0);
        pros::Task* currentTask;
        PIDMode pidMode;
        
        // PID Controllers
        PIDController<Pose>* pidCtrlMove;
        PIDController<double>* pidCtrlTurn;
        
        // Drive control methods
        void tankDrive();
        void arcadeDrive();
        void runAuton();
};

#endif
