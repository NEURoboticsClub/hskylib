#ifndef ROBOT_CONFIG
#define ROBOT_CONFIG

#include "api.h"
#include "utils.h"
#include <vector>

struct DrivebasePorts {
    std::vector<int8_t> brainside;
    std::vector<int8_t> batteryside;
};

struct TransportPorts {
    std::vector<int8_t> brainside;
    std::vector<int8_t> batteryside;
};

struct PortAssignments {
    DrivebasePorts drivebase;
    TransportPorts intake;
    TransportPorts scoring;
    int lady_brown;
    char pneumatics;
};

struct RobotConfig {
    PortAssignments ports;
    pros::motor_brake_mode_e drivebaseBrakeMode;
    pros::motor_gearset_e drivebaseGearset;
    DriveStyle driveStyle;
    double drivebaseSpeedMultiplier; // 0.0 to 1.0
    pros::motor_brake_mode_e intakeBrakeMode;
    pros::motor_gearset_e intakeGearset;
    pros::controller_digital_e_t intakeInButton;
    pros::controller_digital_e_t intakeOutButton;
    double intakeDutyCycle;
    pros::motor_brake_mode_e scoringBrakeMode;
    pros::motor_gearset_e scoringGearset;
    pros::controller_digital_e_t scoringInButton;
    pros::controller_digital_e_t scoringOutButton;
    double scoringDutyCycle;
    pros::controller_digital_e_t pneumaticsExtendButton;
    pros::controller_digital_e_t pneumaticsRetractButton;
    pros::motor_brake_mode_e ladyBrownBrakeMode;
    pros::motor_gearset_e ladyBrownGearset;
    pros::controller_digital_e_t ladyBrownUpButton;
    pros::controller_digital_e_t ladyBrownDownButton;
    double ladyBrownDutyCycle;
};

static DrivebasePorts hsky1DrivebasePorts = {
    {-13, -3, 18},
    {4, 5, -2}
};

static TransportPorts hsky1Intake = {
    {15}, // brainside
    {-11} // batteryside
};

static TransportPorts hsky1Scoring = {
    {8}, // brainside
    {-14} // batteryside
};

static PortAssignments hsky1Ports = {
    hsky1DrivebasePorts,
    hsky1Intake,
    hsky1Scoring,
    17,      // lady brown
    'a',    // pneumatics
};

static RobotConfig hsky1Config = {
    hsky1Ports,
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    ARCADE,
    0.25,
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    pros::E_CONTROLLER_DIGITAL_L1,
    pros::E_CONTROLLER_DIGITAL_L2,
    1.0,
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    pros::E_CONTROLLER_DIGITAL_R1,
    pros::E_CONTROLLER_DIGITAL_R2,
    0.25,
    pros::E_CONTROLLER_DIGITAL_X,
	pros::E_CONTROLLER_DIGITAL_B,
    pros::E_MOTOR_BRAKE_HOLD,
    pros::E_MOTOR_GEAR_200,
    pros::E_CONTROLLER_DIGITAL_UP,
    pros::E_CONTROLLER_DIGITAL_DOWN,
    0.6
};

static DrivebasePorts hsky2DrivebasePorts = {
    {-10, -1, 18},
    {4, 5, -2}
};

static TransportPorts hsky2Intake = {
    {16}, // brainside
    {-6} // batteryside
};

static TransportPorts hsky2Scoring = {
    {9}, // brainside
    {-14} // batteryside
};

static PortAssignments hsky2Ports = {
    hsky2DrivebasePorts,
    hsky2Intake,
    hsky2Scoring,
    20,      // lady brown
    'a',    // pneumatics
};

static RobotConfig hsky2Config = {
    hsky2Ports,
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    ARCADE,
    0.25,
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    pros::E_CONTROLLER_DIGITAL_L1,
    pros::E_CONTROLLER_DIGITAL_L2,
    1.0,
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    pros::E_CONTROLLER_DIGITAL_R1,
    pros::E_CONTROLLER_DIGITAL_R2,
    0.25,
    pros::E_CONTROLLER_DIGITAL_X,
	pros::E_CONTROLLER_DIGITAL_B,
    pros::E_MOTOR_BRAKE_HOLD,
    pros::E_MOTOR_GEAR_200,
    pros::E_CONTROLLER_DIGITAL_UP,
    pros::E_CONTROLLER_DIGITAL_DOWN,
    0.6
};

#endif