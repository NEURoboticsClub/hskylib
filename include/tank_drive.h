#ifndef TANKDRIVE_H
#define TANKDRIVE_H

#include "api.h"
#include "odometry.h"
#include "odometry_drivebase.h"
#include "odometry_three_wheel.h"
#include "pid_controller.h"
#include "pose.h"
#include "robot_config.h"
#include "utils.h"

/**
 * A tank drive drivebase. Contains functions for both manual and
 * autonomous control.
 */
class TankDrive {
  public:
	TankDrive(DrivebaseConfig config, pros::Controller &ctrl);

	~TankDrive();

	// Initialize and start the task
	void initialize(DriveStyle driveStyle);

	// Autonomous movement methods
	void initAuton();
	void driveToPose(Pose *targetPose);
	void turnToHeading(double targetHeadingDegrees);
	void driveDistance(double distIn);
	void driveToPoint(double targetX, double targetY);
	void driveAlongPath(MotionProfile profile);

  private:
	pros::MotorGroup leftMotorGroup;
	pros::MotorGroup rightMotorGroup;
	pros::Controller controller;
	double speedMultiplier;
	Odometry *odom;
	Pose *setPoint = new Pose(0.0, 0.0, 0.0);
	pros::Task *currentTask;
	PIDMode pidMode;

	// PID Controllers
	PIDController<Pose> *pidCtrlMove;
	PIDController<double> *pidCtrlTurn;

	// Drive control methods
	void tankDrive();
	void arcadeDrive();
	void runAuton();
};

#endif
