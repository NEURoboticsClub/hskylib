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
TankDrive tankdrive(config.drivebase, ctrl);
Transport intake(config.intake,
    ctrl);
Transport scoring(config.scoring,
    ctrl);
Pneumatics mogoClamp(config.mogoClamp,
    ctrl);
LadyBrown ladyBrown(config.ladyBrown,
    ctrl);

#endif