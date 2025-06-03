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

class TankDrive {
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
};

#endif
