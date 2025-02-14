#include "tank_drive.h"
#include <cmath>
#include "drive_constants.h"

// constructor
TankDrive::TankDrive(std::vector<int8_t> leftMotors,
    std::vector<int8_t> rightMotors,
    pros::Controller& ctrl,
    pros::motor_brake_mode_e brakeMode,
    pros::motor_gearset_e gearset,
    double speedMultiplier)
        : controller(ctrl),
        speedMultiplier(speedMultiplier),
        leftMotorGroup(leftMotors),
        rightMotorGroup(rightMotors),
        pidMode(OFF) {
            leftMotorGroup.set_brake_mode_all(brakeMode);
            rightMotorGroup.set_brake_mode_all(brakeMode);
            leftMotorGroup.set_gearing_all(gearset);
            rightMotorGroup.set_gearing_all(gearset);
            
            // Initialize PID controllers
            pidCtrlMove = new PIDController<Pose>(DriveConstants::DRIVE_KP, 
                                       DriveConstants::DRIVE_KI, 
                                       DriveConstants::DRIVE_KD);
            pidCtrlTurn = new PIDController<double>(DriveConstants::TURN_KP, 
                                      DriveConstants::TURN_KI, 
                                      DriveConstants::TURN_KD);
            
            odom = new DrivebaseOdometry(leftMotors,
                rightMotors,
                gearset,
                12.376);
            odom->init();
}

TankDrive::~TankDrive() {
    delete pidCtrlMove;
    delete pidCtrlTurn;
    delete setPoint;
    delete currentTask;
}

void TankDrive::runAuton() {
    while (true) {
        Pose currentPose;
        int16_t pidValMove = 0;
        int16_t pidValTurn = 0;
        int16_t maxMotorMag = getInputExtremeForGearset((pros::motor_gearset_e)leftMotorGroup.get_gearing());
        odom->getPose(&currentPose);
        printf("setpoint x: %f, y: %f, theta: %f\n", setPoint->x, setPoint->y, setPoint->theta);
        printf("current x: %f, y: %f, theta: %f\n", currentPose.x, currentPose.y, currentPose.theta);
        if (pidMode == COMBINED) {
            setPoint->theta = atan2((setPoint->y - currentPose.y), (setPoint->x - currentPose.x));
        }
        if (pidMode == DRIVING || pidMode == COMBINED) {
            pidValMove = std::clamp((int16_t)pidCtrlMove->compute(*setPoint, currentPose), (int16_t)((double)maxMotorMag * -1.0 * 0.5), (int16_t)((double)maxMotorMag * 0.5));
        }
        if (pidMode == TURNING || pidMode == COMBINED) {
            pidValTurn = std::clamp((int16_t)pidCtrlTurn->compute(setPoint->theta, currentPose.theta), (int16_t)((double)maxMotorMag * -1.0 * 0.5), (int16_t)((double)maxMotorMag * 0.5));
        }
        
        int16_t motorValLeft = pidValMove - pidValTurn;
        int16_t motorValRight = pidValMove + pidValTurn;

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

void TankDrive::driveToPose(Pose* targetPose) {
    pidMode = COMBINED;
    setPoint->x = targetPose->x;
    setPoint->y = targetPose->y;
    setPoint->theta = targetPose->theta;
}

void TankDrive::turnToHeading(double targetHeadingDegrees) {
    pidMode = TURNING;
    setPoint->theta = (targetHeadingDegrees * 3.14159) / 180.0;
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
        double leftSpeed = (scaleControllerInput(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) / 127.0)
            * (double)getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing())
            * speedMultiplier;
        double rightSpeed = (scaleControllerInput(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y)) / 127.0)
            * (double)getInputExtremeForGearset((pros::motor_gearset_e) rightMotorGroup.get_gearing())
            * speedMultiplier;
        
        leftMotorGroup.move((int)leftSpeed);
        rightMotorGroup.move((int)rightSpeed);

        pros::delay(20);
    }
}

void TankDrive::arcadeDrive() {
    pidMode = OFF;
    while (true) {
        double forwardInput = (scaleControllerInput(controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y)) / 127.0) * speedMultiplier;
        double turnInput = (scaleControllerInput(controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)) / 127.0) * speedMultiplier;

        double leftSpeed = (forwardInput + turnInput) * (double)getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing());
        double rightSpeed = (forwardInput - turnInput)  * (double)getInputExtremeForGearset((pros::motor_gearset_e) rightMotorGroup.get_gearing());

        rightMotorGroup.move((int)rightSpeed);
        leftMotorGroup.move((int)leftSpeed);
        Pose currentPose;
        odom->getPose(&currentPose);
        printf("x: %f, y: %f, theta: %f\n", currentPose.x, currentPose.y, currentPose.theta);

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
