#include "tank_drive.h"
#include <cmath>
#include "drive_constants.h"

// constructor
TankDrive::TankDrive(std::vector<int8_t> leftMotors,
    std::vector<int8_t> rightMotors,
    pros::Controller& ctrl,
    pros::motor_brake_mode_e brakeMode,
    pros::motor_gearset_e gearset,
    double speedMultiplier,
    Odometry* odom)
        : controller(ctrl),
        speedMultiplier(speedMultiplier),
        leftMotorGroup(leftMotors),
        rightMotorGroup(rightMotors),
        odom(odom) {
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
        odom->getPose(&currentPose);
        setPoint->theta = atan2((setPoint->y - currentPose.y), (setPoint->x - currentPose.x));
        int16_t maxMotorMag = getInputExtremeForGearset((pros::motor_gearset_e)leftMotorGroup.get_gearing());
        int16_t pidValMove = std::clamp((int16_t)pidCtrlMove->compute(*setPoint, currentPose), (int16_t)(maxMotorMag * -1), maxMotorMag);
        int16_t pidValTurn = std::clamp((int16_t)pidCtrlTurn->compute(setPoint->theta, currentPose.theta), (int16_t)(maxMotorMag * -1), maxMotorMag);
        int16_t motorValLeft = pidValMove + pidValTurn;
        int16_t motorValRight = pidValMove - pidValTurn;

        leftMotorGroup.move(motorValLeft);
        rightMotorGroup.move(motorValRight);
        pros::delay(20);
    }
}

void TankDrive::initAuton() {
    currentTask = new pros::Task([this] { runAuton(); });
}

void TankDrive::driveToPose(Pose* targetPose) {
    setPoint->x = targetPose->x;
    setPoint->y = targetPose->y;
    setPoint->theta = targetPose->theta;
}

void TankDrive::turnToHeading(double targetHeadingDegrees) {
    setPoint->theta = (targetHeadingDegrees * 3.14159) / 180.0;
}

void TankDrive::driveToPoint(double targetX, double targetY) {
    setPoint->x = targetX;
    setPoint->y = targetY;
}

// void TankDrive::driveDistance(double inches, int maxVelocity) {
//     double targetTicks = inchesToTicks(inches);
//     uint32_t startTime = 0;
//     bool atTarget = false;
    
//     while (true) {
//         Pose currentPose = odom->getPose();
//         printf("Current Position: %f\n", currentPose);
//         double output = pidCtrlMove->compute(targetTicks, currentPose);
//         // Convert PID output to motor velocity
//         int voltage = std::clamp(static_cast<int>(output), -maxVelocity, maxVelocity);
//         printf("Output Voltage: %d\n", voltage);
        
//         leftMotorGroup.move(voltage);
//         rightMotorGroup.move(voltage);
        
//         // Check if we've reached the target
//         if (std::abs(targetTicks - currentPose) < inchesToTicks(DriveConstants::DRIVE_TOLERANCE)) {
//             if (!atTarget) {
//                 startTime = pros::millis();
//                 atTarget = true;
//             }
//             if (pros::millis() - startTime >= 10) {
//                 leftMotorGroup.move(0);
//                 rightMotorGroup.move(0);
//                 break;
//             }
//         } else {
//             atTarget = false;
//         }
        
//         pros::delay(10);
//     }
// }

// void TankDrive::turnAngle(double degrees, int maxVelocity) {
//     double targetTicks = degreesToTicks(degrees);
//     uint32_t startTime = 0;
//     bool atTarget = false;
    
//     while (true) {
//         double leftPos = leftMotorGroup.get_position();
//         double rightPos = rightMotorGroup.get_position();
//         double currentTicks = (leftPos - rightPos) / 2.0;
        
//         double output = pidCtrlTurn->compute(targetTicks, currentTicks);
//         int velocity = std::clamp(static_cast<int>(output), -maxVelocity, maxVelocity);
        
//         leftMotorGroup.move(velocity);
//         rightMotorGroup.move(-velocity);
        
//         if (std::abs(targetTicks - currentTicks) < degreesToTicks(DriveConstants::TURN_TOLERANCE)) {
//             if (!atTarget) {
//                 startTime = pros::millis();
//                 atTarget = true;
//             }
//             if (pros::millis() - startTime >= 10) {
//                 leftMotorGroup.move(0);
//                 rightMotorGroup.move(0);
//                 break;
//             }
//         } else {
//             atTarget = false;
//         }
        
//         pros::delay(10);
//     }
// }

void TankDrive::tankDrive() {
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
