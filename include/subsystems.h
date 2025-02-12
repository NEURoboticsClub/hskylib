#ifndef SUBSYSTEMS_SUBSYSTEMS_H
#define SUBSYSTEMS_SUBSYSTEMS_H

#define PROS_USE_SIMPLE_NAMES
#define PROS_USE_LITERALS

#include "api.h"
#include "tank_drive.h"
#include "transport.h"
#include "lady_brown.h"
#include "pneumatics.h"
#include "robot_config.h"
#include "odometry.h"
#include "odometry_drivebase.h"

pros::Controller ctrl(pros::E_CONTROLLER_MASTER);
RobotConfig config = hsky1Config;
Odometry odom = DrivebaseOdometry(config.ports.intake.brainside,
    config.ports.intake.batteryside,
    pros::E_MOTOR_GEAR_600,
    12.376);
TankDrive tankdrive(config.ports.drivebase.brainside,
    config.ports.drivebase.batteryside,
    ctrl,
    config.drivebaseBrakeMode,
    config.drivebaseGearset,
    config.drivebaseSpeedMultiplier,
    &odom);
Transport intake(config.ports.intake.brainside,
    config.ports.intake.batteryside,
    ctrl,
    config.intakeBrakeMode,
    config.intakeGearset,
    config.intakeInButton,
    config.intakeOutButton,
    config.intakeDutyCycle);
Transport scoring(config.ports.scoring.brainside,
    config.ports.scoring.batteryside,
    ctrl,
    config.scoringBrakeMode,
    config.scoringGearset,
    config.scoringInButton,
    config.scoringOutButton,
    config.scoringDutyCycle);
Pneumatics mogoClamp(config.ports.pneumatics,
    config.pneumaticsExtendButton,
    config.pneumaticsRetractButton,
    ctrl);
LadyBrown ladyBrown(config.ports.lady_brown.arm,
    config.ports.lady_brown.sensor,
    ctrl,
    config.ladyBrownBrakeMode,
    config.ladyBrownGearset,
    config.ladyBrownUpButton,
    config.ladyBrownDownButton,
    pros::E_CONTROLLER_DIGITAL_RIGHT,
    pros::E_CONTROLLER_DIGITAL_LEFT,
    config.ladyBrownDutyCycle,
    config.ladyBrownkP,
    config.ladyBrownkI,
    config.ladyBrownkD,
    config.ladyBrownEaseSetPoint,
    config.ladyBrownArmedSetPoint,
    config.ladyBrownFireSetPoint);

#endif