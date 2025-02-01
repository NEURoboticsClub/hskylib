#ifndef TANKDRIVE_H
#define TANKDRIVE_H

#include "api.h"
#include "utils.h"
#include "PIDController.h"
#include "drive_constants.h"

class TankDrive {
private:
    pros::MotorGroup leftMotorGroup = {};
    pros::MotorGroup rightMotorGroup = {};
    pros::Controller controller;
    
    // PID Controllers
    PIDController* drivePID;
    PIDController* turnPID;
    
    // Helper functions
    double inchesToTicks(double inches);
    double ticksToInches(double ticks);
    double degreesToTicks(double degrees);
    void resetEncoders();
    double getAveragePosition();
    
    // Drive control methods
    void tankDrive();
    void arcadeDrive();

public:
    TankDrive(pros::MotorGroup& leftMotors,
        pros::MotorGroup& rightMotors,
        pros::Controller& ctrl,
        pros::motor_brake_mode_e brakeMode,
        pros::motor_gearset_e gearset);
    
    ~TankDrive();

    // initialize and start the task
    void initialize(DriveStyle driveStyle);
    
    // Autonomous movement methods
    void driveDistance(double inches, int maxVelocity = DriveConstants::MAX_DRIVE_VELOCITY);
    void turnAngle(double degrees, int maxVelocity = DriveConstants::MAX_TURN_VELOCITY);
    bool isMoving();
};

#endif
