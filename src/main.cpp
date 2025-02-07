#include "main.h"

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	printf("starting opcontrol");
	pros::Controller ctrl(pros::E_CONTROLLER_MASTER);
	RobotConfig config = hsky2Config;
	Odometry odom = DrivebaseOdometry(config.ports.intake.brainside,
        config.ports.intake.batteryside,pros::E_MOTOR_GEAR_600,12.376);

	TankDrive tankdrive(config.ports.drivebase.brainside, config.ports.drivebase.batteryside, ctrl, config.drivebaseBrakeMode, config.drivebaseGearset, config.drivebaseSpeedMultiplier,&odom);
	
	tankdrive.initialize(config.driveStyle);

	Transport intake(config.ports.intake.brainside,
        config.ports.intake.batteryside,
        ctrl,
        config.intakeBrakeMode,
        config.intakeGearset,
        config.intakeInButton,
        config.intakeOutButton,
        config.intakeDutyCycle);
	
	intake.initialize();

	Transport scoring(config.ports.scoring.brainside,
        config.ports.scoring.batteryside,
        ctrl,
        config.scoringBrakeMode,
        config.scoringGearset,
        config.scoringInButton,
        config.scoringOutButton,
        config.scoringDutyCycle);
	
	scoring.initialize();

	Pneumatics mogoClamp(config.ports.pneumatics,
		config.pneumaticsExtendButton,
		config.pneumaticsRetractButton,
		ctrl);

	mogoClamp.initialize();

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
	
	ladyBrown.initialize();

	while (true) {
		pros::delay(50);
	}
}