#include "tank_drive.h"

#include <cmath>

// constructor
TankDrive::TankDrive(DrivebaseConfig config, pros::Controller &ctrl)
	: controller(ctrl),
	  speedMultiplier(config.speedMultiplier),
	  leftMotorGroup(config.brainside),
	  rightMotorGroup(config.batteryside),
	  pidMode(OFF) {
	leftMotorGroup.set_brake_mode_all(config.brakeMode);
	rightMotorGroup.set_brake_mode_all(config.brakeMode);
	leftMotorGroup.set_gearing_all(config.gearset);
	rightMotorGroup.set_gearing_all(config.gearset);

	// Initialize PID controllers
	pidCtrlMove = new PIDController<Pose>(config.autonConstants.kPDrive,
										  config.autonConstants.kIDrive,
										  config.autonConstants.kDDrive);
	pidCtrlTurn = new PIDController<double>(config.autonConstants.kPTurn,
											config.autonConstants.kITurn,
											config.autonConstants.kDTurn);

	pidCtrlPath = new PIDController<double>(1, 0, 0); // TODO: tune path PID

	odom = new DrivebaseOdometry(config.brainside, config.batteryside,
								 config.gearset,
								 config.autonConstants.trackWidthIn);
	odom->init();
}

TankDrive::~TankDrive() {
	delete pidCtrlMove;
	delete pidCtrlTurn;
	delete pidCtrlPath;
	delete setPoint;
	delete currentTask;
}

void TankDrive::runAuton() {
	while (true) {
		Pose currentPose;
		int16_t pidValMove = 0;
		int16_t pidValTurn = 0;
		int16_t maxMotorMag = getInputExtremeForGearset(
			(pros::motor_gearset_e)leftMotorGroup.get_gearing());
		odom->getPose(&currentPose);
		// printf("setpoint x: %f, y: %f, theta: %f\n", setPoint->x,
		// setPoint->y, setPoint->theta); printf("current x: %f, y: %f, theta:
		// %f\n", currentPose.x, currentPose.y, currentPose.theta);
		if (pidMode == COMBINED) {
			setPoint->theta = atan2((setPoint->y - currentPose.y),
									(setPoint->x - currentPose.x));
		}
		if (pidMode == DRIVING || pidMode == COMBINED) {
			double moveComputation =
				pidCtrlMove->compute(*setPoint, currentPose);
			printf("move: %f\n", moveComputation);
			pidValMove =
				std::clamp(moveComputation, ((double)maxMotorMag * -1.0 * 0.5),
						   ((double)maxMotorMag * 0.5));
		}
		if (pidMode == TURNING || pidMode == COMBINED) {
			double turnComputation =
				pidCtrlTurn->compute(setPoint->theta, currentPose.theta);
			printf("turn: %f\n", turnComputation);
			pidValTurn =
				std::clamp(turnComputation, ((double)maxMotorMag * -1.0 * 0.5),
						   ((double)maxMotorMag * 0.5));
		}

		int16_t motorValLeft = pidValMove - pidValTurn;
		int16_t motorValRight = pidValMove + pidValTurn;
		printf("left motors: %d\n", motorValLeft);
		printf("right motors: %d\n", motorValRight);

		if (pidMode != OFF) {
			leftMotorGroup.move(motorValLeft);
			rightMotorGroup.move(motorValRight);
		}

		pros::delay(20);
	}
}

void TankDrive::initAuton() {
	currentTask = new pros::Task([this] { runAuton(); });
}

void TankDrive::driveAlongPath(MotionProfile profile) {
	Pose currentPose;
	Pose lastPose;
	odom->getPose(&lastPose);

	double currentVelocity = 0.0;
	double lastTime = pros::millis();
	while (true) {
		odom->getPose(&currentPose);

		// Calculate current velocity in some units per second
		currentVelocity =
			std::hypot(currentPose.x - lastPose.x,
						currentPose.y - lastPose.y) /
			((pros::millis() - lastTime) / 1000.0);

		double maxMotorMag = (double)getInputExtremeForGearset(
			(pros::motor_gearset_e)leftMotorGroup.get_gearing());

		double targetVelocity = profile.getVelocityFromPosition(currentPose);
		double calculatedPathPower = pidCtrlPath->compute(targetVelocity, currentVelocity);
		calculatedPathPower = std::clamp(calculatedPathPower, -maxMotorMag, maxMotorMag);

		// TODO: Add pure pursuit stuff here

		leftMotorGroup.move(calculatedPathPower);
		rightMotorGroup.move(calculatedPathPower);

		pros::delay(20);
	}
}

void TankDrive::driveToPose(Pose *targetPose) {
	pidMode = COMBINED;
	setPoint->x = targetPose->x;
	setPoint->y = targetPose->y;
	setPoint->theta = targetPose->theta;
}

void TankDrive::turnToHeading(double targetHeadingDegrees) {
	pidMode = TURNING;
	setPoint->theta = (targetHeadingDegrees * M_PI) / 180.0;
}

void TankDrive::driveToPoint(double targetX, double targetY) {
	pidMode = COMBINED;
	setPoint->x = targetX;
	setPoint->y = targetY;
}

void TankDrive::driveDistance(double distIn) {
	pidMode = DRIVING;
	Pose currentPose;
	odom->getPose(&currentPose);
	setPoint->x = distIn * (cos(currentPose.theta));
	setPoint->y = distIn * (sin(currentPose.theta));
}

void TankDrive::tankDrive() {
	pidMode = OFF;
	while (true) {
		double leftSpeed =
			(scaleControllerInput(
				 controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) /
			 127.0) *
			(double)getInputExtremeForGearset(
				(pros::motor_gearset_e)leftMotorGroup.get_gearing()) *
			speedMultiplier;
		double rightSpeed =
			(scaleControllerInput(
				 controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) /
			 127.0) *
			(double)getInputExtremeForGearset(
				(pros::motor_gearset_e)rightMotorGroup.get_gearing()) *
			speedMultiplier;

		leftMotorGroup.move((int)leftSpeed);
		rightMotorGroup.move((int)rightSpeed);

		pros::delay(20);
	}
}

void TankDrive::arcadeDrive() {
	pidMode = OFF;
	while (true) {
		double forwardInput = (scaleControllerInput(controller.get_analog(
								   pros::E_CONTROLLER_ANALOG_LEFT_Y)) /
							   127.0) *
							  speedMultiplier;
		double turnInput = (scaleControllerInput(controller.get_analog(
								pros::E_CONTROLLER_ANALOG_RIGHT_X)) /
							127.0) *
						   speedMultiplier;

		double leftSpeed =
			(forwardInput + turnInput) *
			(double)getInputExtremeForGearset(
				(pros::motor_gearset_e)leftMotorGroup.get_gearing());
		double rightSpeed =
			(forwardInput - turnInput) *
			(double)getInputExtremeForGearset(
				(pros::motor_gearset_e)rightMotorGroup.get_gearing());

		rightMotorGroup.move((int)rightSpeed);
		leftMotorGroup.move((int)leftSpeed);
		Pose currentPose;
		odom->getPose(&currentPose);
		printf("x: %f, y: %f, theta: %f\n", currentPose.x, currentPose.y,
			   currentPose.theta);

		pros::delay(20);
	}
}

void TankDrive::initialize(DriveStyle driveStyle) {
	if (driveStyle == ARCADE) {
		currentTask = new pros::Task([this] { arcadeDrive(); });
	} else if (driveStyle == TANK) {
		currentTask = new pros::Task([this] { tankDrive(); });
	}
}
