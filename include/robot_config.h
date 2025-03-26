#ifndef ROBOT_CONFIG
#define ROBOT_CONFIG

#include "api.h"
#include "utils.h"
#include <vector>

struct AutonConstants {
    double wheelDiameterIn;
    double trackWidthIn;
    double ticksPerRev; // encoder ticks per revolution
    
    double kPDrive; 
    double kIDrive;
    double kDDrive;
    
    double kPTurn;
    double kITurn;
    double kDTurn;
    
    double driveToleranceIn;
    double turnToleranceDeg;
    
    double maxDriveVelocityDutyCycle;  // velocity units
    double maxTurnVelocityDutyCycle;   // velocity units
};

struct DrivebaseConfig {
    std::vector<int8_t> brainside;
    std::vector<int8_t> batteryside;
    pros::motor_brake_mode_e brakeMode;
    pros::motor_gearset_e gearset;
    DriveStyle driveStyle;
    double speedMultiplier; // 0.0 to 1.0
    AutonConstants autonConstants;
};

struct TransportConfig {
    std::vector<int8_t> motors;
    pros::motor_brake_mode_e brakeMode;
    pros::motor_gearset_e gearset;
    pros::controller_digital_e_t inButton;
    pros::controller_digital_e_t outButton;
    double dutyCycle;
};

struct PneumaticsConfig {
    char port;
    pros::controller_digital_e_t extendButton;
    pros::controller_digital_e_t retractButton;
};

struct LadyBrownConfig {
    int8_t armPort;
    int8_t sensorPort;
    pros::motor_brake_mode_e brakeMode;
    pros::motor_gearset_e gearset;
    pros::controller_digital_e_t upButton;
    pros::controller_digital_e_t downButton;
    pros::controller_digital_e_t macroForwardButton;
    pros::controller_digital_e_t macroBackButton;
    double dutyCycle;
    double kP;
    double kI;
    double kD;
    uint32_t easeSetPoint;
    uint32_t armedSetPoint;
    uint32_t fireSetPoint;
};

struct RobotConfig {
    DrivebaseConfig drivebase;
    TransportConfig intake;
    TransportConfig scoring;
    PneumaticsConfig mogoClamp;
    LadyBrownConfig ladyBrown;
};

static AutonConstants hsky1AutonConstants = {
    3.25,
    12.376,
    300.0*57.0/39.0, // encoder ticks per revolution
    
    1, 
    0.0,
    0.1,
    
    2,
    0.05,
    0.1,
    
    0.5,
    1.0,
    
    1.0,  // velocity units
    1.0   // velocity units
};

static DrivebaseConfig hsky1Drivebase = {
    {-12, -11, 13},
    {2, 1, -3},
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    ARCADE,
    0.25,
    hsky1AutonConstants
};

static TransportConfig hsky1Intake = {
    {21, -18},
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    pros::E_CONTROLLER_DIGITAL_L1,
    pros::E_CONTROLLER_DIGITAL_L2,
    1.0
};

static TransportConfig hsky1Scoring = {
    {15, -16},
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    pros::E_CONTROLLER_DIGITAL_R1,
    pros::E_CONTROLLER_DIGITAL_R2,
    0.25
};

static PneumaticsConfig hsky1MogoClamp = {
    'a',
    pros::E_CONTROLLER_DIGITAL_B,
	pros::E_CONTROLLER_DIGITAL_X
};

static LadyBrownConfig hsky1LadyBrown = {
    21,
    21,
    pros::E_MOTOR_BRAKE_HOLD,
    pros::E_MOTOR_GEAR_100,
    pros::E_CONTROLLER_DIGITAL_UP,
    pros::E_CONTROLLER_DIGITAL_DOWN,
    pros::E_CONTROLLER_DIGITAL_RIGHT,
    pros::E_CONTROLLER_DIGITAL_LEFT,
    0.6,
    0.01,
    0.0,
    0.00,
    0,
    7800,
    40000
};

static RobotConfig hsky1Config = {
    hsky1Drivebase,
    hsky1Intake,
    hsky1Scoring,
    hsky1MogoClamp,
    hsky1LadyBrown
};

static AutonConstants hsky2AutonConstants = {
    3.25,
    12.376,
    300.0*57.0/39.0, // encoder ticks per revolution
    
    1, 
    0.0,
    0.1,
    
    2,
    0.05,
    0.1,
    
    0.5,
    1.0,
    
    1.0,  // velocity units
    1.0   // velocity units
};

static DrivebaseConfig hsky2Drivebase = {
    {-10, -1, 18},
    {4, 5, -2},
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    ARCADE,
    0.25,
    hsky2AutonConstants
};

static TransportConfig hsky2Intake = {
    {-16,6},
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    pros::E_CONTROLLER_DIGITAL_L1,
    pros::E_CONTROLLER_DIGITAL_L2,
    1.0
};

static TransportConfig hsky2Scoring = {
    {9,-14},
    pros::E_MOTOR_BRAKE_COAST,
    pros::E_MOTOR_GEAR_600,
    pros::E_CONTROLLER_DIGITAL_R1,
    pros::E_CONTROLLER_DIGITAL_R2,
    0.25
};

static PneumaticsConfig hsky2MogoClamp = {
    'a',
    pros::E_CONTROLLER_DIGITAL_X,
	pros::E_CONTROLLER_DIGITAL_B
};

static LadyBrownConfig hsky2LadyBrown = {
    19,
    20,
    pros::E_MOTOR_BRAKE_HOLD,
    pros::E_MOTOR_GEAR_100,
    pros::E_CONTROLLER_DIGITAL_UP,
    pros::E_CONTROLLER_DIGITAL_DOWN,
    pros::E_CONTROLLER_DIGITAL_RIGHT,
    pros::E_CONTROLLER_DIGITAL_LEFT,
    0.6,
    0.01,
    0.0,
    0.00,
    0,
    7500,
    40000
};

static RobotConfig hsky2Config = {
    hsky2Drivebase,
    hsky2Intake,
    hsky2Scoring,
    hsky2MogoClamp,
    hsky2LadyBrown
};

#endif