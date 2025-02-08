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

struct LadyBrownPorts {
    int8_t arm;
    int8_t sensor;
};

struct PortAssignments {
    DrivebasePorts drivebase;
    TransportPorts intake;
    TransportPorts scoring;
    LadyBrownPorts lady_brown;
    char pneumatics;
};

// struct DriveConstants {
//     double WHEEL_DIAMETER = 3.25;  // inches
//     double WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * M_PI;
//     double TRACK_WIDTH = 12.376;    // distance between wheels in inches
//     double TICKS_PER_REV = 300.0*57.0/39.0; // encoder ticks per revolution
    
//     double kPDrive = 1; 
//     double kIDrive = 0.0;
//     double kDDrive = 0.1;
    
//     double kPTurn = 2;
//     double kITurn = 0.05;
//     double kDTurn = 0.1;
    
//     double driveTolerance = 0.5;  // inches
//     double turnTolerance = 1.0;   // degrees
    
//     double maxDriveVelocityDutyCycle = 1.0;  // velocity units
//     double maxTurnVelocityDutyCycle = 1.0;   // velocity units
// };

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
    pros::controller_digital_e_t ladyBrownEaseButton;
    pros::controller_digital_e_t ladyBrownArmedButton;
    pros::controller_digital_e_t ladyBrownFireButton;
    double ladyBrownDutyCycle;
    double ladyBrownkP;
    double ladyBrownkI;
    double ladyBrownkD;
    uint32_t ladyBrownEaseSetPoint;
    uint32_t ladyBrownArmedSetPoint;
    uint32_t ladyBrownFireSetPoint;
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

static LadyBrownPorts hsky1LadyBrown = {
    17,
    13
};

static PortAssignments hsky1Ports = {
    hsky1DrivebasePorts,
    hsky1Intake,
    hsky1Scoring,
    hsky1LadyBrown,
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
    pros::E_CONTROLLER_DIGITAL_LEFT,
    pros::E_CONTROLLER_DIGITAL_RIGHT,
    pros::E_CONTROLLER_DIGITAL_LEFT, // TODO: fix button and sensor port assignments for lady brown
    0.6,
    0.005,
    0.0,
    0.0,
    0,
    0,
    0
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

static LadyBrownPorts hsky2LadyBrown = {
    19,
    20
};

static PortAssignments hsky2Ports = {
    hsky2DrivebasePorts,
    hsky2Intake,
    hsky2Scoring,
    hsky2LadyBrown,
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
    pros::E_MOTOR_GEAR_100,
    pros::E_CONTROLLER_DIGITAL_UP,
    pros::E_CONTROLLER_DIGITAL_DOWN,
    pros::E_CONTROLLER_DIGITAL_LEFT,
    pros::E_CONTROLLER_DIGITAL_RIGHT,
    pros::E_CONTROLLER_DIGITAL_LEFT, // TODO: fix button and sensor port assignments for lady brown
    0.6,
    0.01,
    0.0,
    0.00,
    0,
    7500,
    40000
};

#endif