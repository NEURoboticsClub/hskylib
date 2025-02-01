#include "tank_drive.h"
#include <cmath>
#include "drive_constants.h"

// constructor
TankDrive::TankDrive(pros::MotorGroup& leftMotors,
    pros::MotorGroup& rightMotors,
    pros::Controller& ctrl,
    pros::motor_brake_mode_e brakeMode,
    pros::motor_gearset_e gearset)
        : controller(ctrl) {
            leftMotorGroup.append(leftMotors);
            rightMotorGroup.append(rightMotors);
            leftMotorGroup.set_brake_mode_all(brakeMode);
            rightMotorGroup.set_brake_mode_all(brakeMode);
            leftMotorGroup.set_gearing_all(gearset);
            rightMotorGroup.set_gearing_all(gearset);
            
            // Initialize PID controllers
            drivePID = new PIDController(DriveConstants::DRIVE_KP, 
                                       DriveConstants::DRIVE_KI, 
                                       DriveConstants::DRIVE_KD);
            turnPID = new PIDController(DriveConstants::TURN_KP, 
                                      DriveConstants::TURN_KI, 
                                      DriveConstants::TURN_KD);
}

TankDrive::~TankDrive() {
    delete drivePID;
    delete turnPID;
}

double TankDrive::inchesToTicks(double inches) {
    return (inches / DriveConstants::WHEEL_CIRCUMFERENCE) * DriveConstants::TICKS_PER_REV;
}

double TankDrive::ticksToInches(double ticks) {
    return (ticks / DriveConstants::TICKS_PER_REV) * DriveConstants::WHEEL_CIRCUMFERENCE;
}

double TankDrive::degreesToTicks(double degrees) {
    double arcLength = (degrees / 360.0) * (DriveConstants::TRACK_WIDTH * M_PI);
    return inchesToTicks(arcLength);
}

void TankDrive::resetEncoders() {
    leftMotorGroup.tare_position();
    rightMotorGroup.tare_position();
}

double TankDrive::getAveragePosition() {
    return (leftMotorGroup.get_position() + rightMotorGroup.get_position()) / 2.0;
}

void TankDrive::driveDistance(double inches, int maxVelocity) {
    resetEncoders();
    double targetTicks = inchesToTicks(inches);
    uint32_t startTime = 0;
    bool atTarget = false;
    
    while (true) {
        double currentPosition = getAveragePosition();
        printf("Current Position: %f\n", currentPosition);
        double output = drivePID->compute(targetTicks, currentPosition);
        // Convert PID output to motor velocity
        int voltage = std::clamp(static_cast<int>(output), -maxVelocity, maxVelocity);
        printf("Output Voltage: %d\n", voltage);
        
        leftMotorGroup.move(voltage);
        rightMotorGroup.move(voltage);
        
        // Check if we've reached the target
        if (std::abs(targetTicks - currentPosition) < inchesToTicks(DriveConstants::DRIVE_TOLERANCE)) {
            if (!atTarget) {
                startTime = pros::millis();
                atTarget = true;
            }
            if (pros::millis() - startTime >= 10) {
                leftMotorGroup.move(0);
                rightMotorGroup.move(0);
                break;
            }
        } else {
            atTarget = false;
        }
        
        pros::delay(10);
    }
}

void TankDrive::turnAngle(double degrees, int maxVelocity) {
    resetEncoders();
    double targetTicks = degreesToTicks(degrees);
    uint32_t startTime = 0;
    bool atTarget = false;
    
    while (true) {
        double leftPos = leftMotorGroup.get_position();
        double rightPos = rightMotorGroup.get_position();
        double currentTicks = (leftPos - rightPos) / 2.0;
        
        double output = turnPID->compute(targetTicks, currentTicks);
        int velocity = std::clamp(static_cast<int>(output), -maxVelocity, maxVelocity);
        
        leftMotorGroup.move(velocity);
        rightMotorGroup.move(-velocity);
        
        if (std::abs(targetTicks - currentTicks) < degreesToTicks(DriveConstants::TURN_TOLERANCE)) {
            if (!atTarget) {
                startTime = pros::millis();
                atTarget = true;
            }
            if (pros::millis() - startTime >= 10) {
                leftMotorGroup.move(0);
                rightMotorGroup.move(0);
                break;
            }
        } else {
            atTarget = false;
        }
        
        pros::delay(10);
    }
}

void TankDrive::tankDrive() {
    while (true) {
        float leftInput = (float)controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;
        float rightInput = (float)controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0;
        if (abs(leftInput) > 0.05) {
            int leftSpeed = leftInput * getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing());
            leftMotorGroup.move(leftSpeed);
        }
        if (abs(rightInput) > 0.05) {
            int rightSpeed = rightInput * getInputExtremeForGearset((pros::motor_gearset_e) rightMotorGroup.get_gearing());
            rightMotorGroup.move(rightSpeed);
        }

        pros::delay(20);
    }
}

void TankDrive::arcadeDrive() {
    while (true) {
        float forwardInput = (float)controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0;
        float turnInput = (float)controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X) / 127.0;

        float leftSpeed = 0.0;
        float rightSpeed = 0.0;
        if (forwardInput > 0.05 || forwardInput < -0.05) {
            leftSpeed += forwardInput * (float)getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing());
            rightSpeed += forwardInput * (float)getInputExtremeForGearset((pros::motor_gearset_e) rightMotorGroup.get_gearing());
        }
        if (turnInput > 0.05 || turnInput < -0.05) {
            leftSpeed += turnInput * (float)getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing());
            rightSpeed -= turnInput * (float)getInputExtremeForGearset((pros::motor_gearset_e) leftMotorGroup.get_gearing());
        }

        leftSpeed *= 0.4;
        rightSpeed *= 0.4;

        rightMotorGroup.move((int)rightSpeed);
        leftMotorGroup.move((int)leftSpeed);

        pros::delay(20);
    }
}

void TankDrive::initialize(DriveStyle driveStyle) {
    if (driveStyle == ARCADE) {
        pros::Task task([this] { arcadeDrive(); });
    } else if (driveStyle == TANK) {
        pros::Task task([this] { tankDrive(); });
    }
}
