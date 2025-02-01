#include "main.h"
// #include <iostream>

// /**
//  * A callback function for LLEMU's center button.
//  *
//  * When this callback is fired, it will toggle line 2 of the LCD text between
//  * "I was pressed!" and nothing.
//  */
// void on_center_button() {
// 	static bool pressed = false;
// 	pressed = !pressed;
// 	if (pressed) {
// 		pros::lcd::set_text(2, "I was pressed!");
// 	} else {
// 		pros::lcd::clear_line(2);
// 	}
// }

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	// pros::lcd::initialize();
	// pros::lcd::set_text(1, "Hello PROS User!");

	// pros::lcd::register_btn1_cb(on_center_button);
}

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
void autonomous() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({-1,18,-10});
	pros::MotorGroup right_mg({5,-2,4});
	TankDrive drive(left_mg, right_mg, master, pros::E_MOTOR_BRAKE_BRAKE, pros::E_MOTOR_GEAR_GREEN);
	pros::ADIDigitalOut pneumatic('a');
	// // Drive forward 24 inches
	// drive.driveDistance(24.0);
	// pros::delay(200);
	
	// // Turn 90 degrees clockwise
	// drive.turnAngle(90.0);
	// pros::delay(200);
	
	// Drive forward 12 inches at half speed
	// drive.driveDistance(-24, DriveConstants::MAX_DRIVE_VELOCITY / 2);
	// drive.driveDistance(24, DriveConstants::MAX_DRIVE_VELOCITY / 2);
	// while(true){
	// drive.turnAngle(90, DriveConstants::MAX_TURN_VELOCITY / 3);
	// pros::delay(1000);
	// drive.turnAngle(-90, DriveConstants::MAX_TURN_VELOCITY / 3);
	// pros::delay(1000);
	// drive.turnAngle(-90, DriveConstants::MAX_TURN_VELOCITY / 3);
	// pros::delay(1000);
	// drive.turnAngle(90, DriveConstants::MAX_TURN_VELOCITY / 3);
	// pros::delay(1000);
	// }
	pros::MotorGroup intake_left_mg({16}); //-5    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup intake_right_mg({-9});
	Transport intake(intake_left_mg,
        intake_right_mg,
        master,
        pros::E_MOTOR_BRAKE_COAST,
        pros::E_MOTOR_GEAR_600,
        pros::E_CONTROLLER_DIGITAL_L2,
        pros::E_CONTROLLER_DIGITAL_L1,
        0.5);

	pros::MotorGroup lift_left_mg({8}); //-5    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup lift_right_mg({-14});

	Transport lift(lift_left_mg,
        lift_right_mg,
        master,
        pros::E_MOTOR_BRAKE_COAST,
        pros::E_MOTOR_GEAR_600,
        pros::E_CONTROLLER_DIGITAL_R1,
        pros::E_CONTROLLER_DIGITAL_R2,
        0.75);
	 pneumatic.set_value(true);
	 drive.driveDistance(-20.0, DriveConstants::MAX_DRIVE_VELOCITY / 3);
	//  drive.driveDistance-3.0, DriveConstants::MAX_DRIVE_VELOCITY / 2);
	//  drive.driveDistance(-23.0, DriveConstants::MAX_DRIVE_VELOCITY / 3);
	 pros::delay(30);
	 drive.turnAngle(45, DriveConstants::MAX_TURN_VELOCITY / 3);
	 pros::delay(30);
	 drive.driveDistance(-15.0, DriveConstants::MAX_DRIVE_VELOCITY / 3);
	 pros::delay(30);
	 drive.driveDistance(5.0, DriveConstants::MAX_DRIVE_VELOCITY / 3);
	 drive.turnAngle(-59, DriveConstants::MAX_TURN_VELOCITY / 4);
	 drive.driveDistance(-23.5, DriveConstants::MAX_DRIVE_VELOCITY / 4);
	 pneumatic.set_value(false);
	 drive.driveDistance(12.0, DriveConstants::MAX_DRIVE_VELOCITY / 3);
	 intake.moveOut();
	 lift.moveIn();
	 drive.driveDistance(28.0, DriveConstants::MAX_DRIVE_VELOCITY / 3);
	// drive.driveDistance(24.0, DriveConstants::MAX_DRIVE_VELOCITY / 3);
	
	// pros::delay(10);
	// drive.turnAngle(180, DriveConstants::MAX_TURN_VELOCITY / 4);
	// pros::delay(10);
	// drive.driveDistance(24.0, DriveConstants::MAX_DRIVE_VELOCITY / 3);
	// pros::delay(10);
	// drive.turnAngle(180, DriveConstants::MAX_TURN_VELOCITY / 4);
	// pros::delay(10);
	// drive.driveDistance(24.0, DriveConstants::MAX_DRIVE_VELOCITY / 3);
	// pros::delay(10);
	// drive.driveDistance(-24.0, DriveConstants::MAX_DRIVE_VELOCITY / 3);
	// drive.driveDistance(24.0, DriveConstants::MAX_DRIVE_VELOCITY / 2);
	// drive.turnAngle(180, DriveConstants::MAX_TURN_VELOCITY / 3);
	// drive.driveDistance(24.0, DriveConstants::MAX_DRIVE_VELOCITY / 2);
	// drive.driveDistance(-24.0, DriveConstants::MAX_DRIVE_VELOCITY / 2);
	pros::delay(10);
	// drive.turnAngle(-90, DriveConstants::MAX_TURN_VELOCITY / 3);
	// drive.driveDistance(-24.0, DriveConstants::MAX_DRIVE_VELOCITY / 2);
}

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
	autonomous();
	return;
	// std::array<float, 12> thing = {0};
	// UpdateTuningDisplay(thing);
	printf("starting opcontrol");
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({-1,18,-10}); //-5    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({5,-2,4}); //-2  // Creates a motor group with forwards port 5 and reversed ports 4 & 6

	// left_mg.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
	// right_mg.set_brake_mode_all(pros::E_MOTOR_BRAKE_BRAKE);
	// left_mg.set_gearing_all(pros::E_MOTOR_GEAR_BLUE);
	// right_mg.set_gearing_all(pros::E_MOTOR_GEAR_BLUE);
	// printf("Test");

	// while (true) {
    //     int leftSpeed = ((float)master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) / 127.0) * 600;
    //     int rightSpeed = ((float)master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y) / 127.0) * 600;

    //     right_mg.move(rightSpeed);
    //     left_mg.move(leftSpeed);
	// 	printf("%d", leftSpeed);

    //     pros::delay(20);
    // }

	// printf("Constructing tank drive");
	TankDrive tankdrivefku(left_mg, right_mg, master, pros::E_MOTOR_BRAKE_COAST, pros::E_MOTOR_GEAR_600);
	tankdrivefku.initialize(DriveStyle::ARCADE);

	pros::MotorGroup intake_left_mg({16}); //-5    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup intake_right_mg({-9});

	Transport intake(intake_left_mg,
        intake_right_mg,
        master,
        pros::E_MOTOR_BRAKE_COAST,
        pros::E_MOTOR_GEAR_600,
        pros::E_CONTROLLER_DIGITAL_L2,
        pros::E_CONTROLLER_DIGITAL_L1,
        0.5);
	
	intake.initialize();

	pros::MotorGroup lift_left_mg({8}); //-5    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup lift_right_mg({-14});

	Transport lift(lift_left_mg,
        lift_right_mg,
        master,
        pros::E_MOTOR_BRAKE_COAST,
        pros::E_MOTOR_GEAR_600,
        pros::E_CONTROLLER_DIGITAL_R1,
        pros::E_CONTROLLER_DIGITAL_R2,
        0.5);
	
	lift.initialize();

	// while (true) {
	// 	pros::delay(50);
	// }
	pros::ADIDigitalOut pneumatic('a');
	pros::Motor arm_motor(20);
	arm_motor.set_brake_mode(pros::MotorBrake::hold);
	while (true) {
		
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_X)) {
			pneumatic.set_value(true);  // Extend the pneumatic
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_B)) {
			pneumatic.set_value(false); // Retract the pneumatic
		}
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_UP)) {
			arm_motor.move_velocity(75);  // Move the arm up
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN)) {
			arm_motor.move_velocity(-75); // Move the arm down
		} else {
			arm_motor.set_brake_mode(pros::MotorBrake::hold);
			arm_motor.brake();    // Stop the arm
		}
		pros::delay(50);
	}



	// while (true) {
	// 	pros::delay(20);
	// }

	// while (true) {
	// 	pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
	// 	                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
	// 	                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs

	// 	// Arcade control scheme
	// 	int dir = master.get_analog(ANALOG_LEFT_Y);    // Gets amount forward/backward from left joystick
	// 	int turn = master.get_analog(ANALOG_RIGHT_X);  // Gets the turn left/right from right joystick
	// 	left_mg.move(dir - turn);                      // Sets left motor voltage
	// 	right_mg.move(dir + turn);                     // Sets right motor voltage
	// 	pros::delay(20);                               // Run for 20 ms then update
	// }
}