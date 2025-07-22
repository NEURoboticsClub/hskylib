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
void autonomous() {
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
	printf("starting opcontrol");

	// tankdrive.driveToPoint(6.0,6.0);
	// tankdrive.turnToHeading(90.0);
	// tankdrive.driveDistance(6.0);
	// tankdrive.initAuton();
	// pros::delay(10000);
	// tankdrive.driveDistance(-6.0);

	tankdrive.initialize(config.drivebase.driveStyle);
	
	intake.initialize();
	
	scoring.initialize();

	mogoClamp.initialize();
	
	ladyBrown.initialize();
	
	// pros::screen_touch_status_s_t status;
	
	while (true) {
		int HEIGHT = 272;
		int WIDTH = 480;

		int squares = 5;
		int square_spacing = 25;
		int top_padding = 10;
		int bottom_padding = 40;
		int square_size = 65;
		int left_padding = (WIDTH - (squares  * (square_size + square_spacing)) + square_spacing) / 2;
		
		pros::screen::set_pen(pros::Color::grey);
		for (int i = 0; i < squares; i++) {
			pros::screen::draw_rect(left_padding + (square_spacing + square_size) * i, top_padding, left_padding + (square_spacing + square_size) * i + square_size, top_padding + square_size);
			pros::screen::draw_rect(left_padding + (square_spacing + square_size) * i, HEIGHT - bottom_padding - square_size, left_padding + (square_spacing + square_size) * i + square_size, HEIGHT - bottom_padding);
		}
		pros::screen::set_pen(pros::Color::red);
		int color_seperation = square_spacing;
		int color_rect_height = square_size;
		int width = WIDTH / 2 - color_seperation / 2 - 20;
		
		
		pros::screen::draw_rect(left_padding, HEIGHT / 2 - color_rect_height / 2 - 15, left_padding + width, HEIGHT / 2 + color_rect_height - color_rect_height / 2 - 15);
		pros::screen::set_pen(pros::Color::blue);
		pros::screen::draw_rect(left_padding + width + color_seperation / 2, HEIGHT / 2 - color_rect_height / 2 - 15, left_padding + width + width + color_seperation / 2, HEIGHT / 2 + color_rect_height - color_rect_height / 2 - 15);


		// status = pros::screen::touch_status();
		// pros::screen::print(TEXT_MEDIUM, 1, "Touch Status (Type): %d", status.touch_status);
        // pros::screen::print(TEXT_MEDIUM, 2, "Last X: %d", status.x);
        // pros::screen::print(TEXT_MEDIUM, 3, "Last Y: %d", status.y);
        // pros::screen::print(TEXT_MEDIUM, 4, "Press Count: %d", status.press_count);
        // pros::screen::print(TEXT_MEDIUM, 5, "Release Count: %d", status.release_count);
		// // pros::c::screen_draw_pixel(status.x, status.y);
		// pros::screen::fill_rect(status.x - 5, status.y - 5, status.x + 5, status.y + 5);
		// // for (int i = 0; i < HEIGHT; i++) {
		// 	for (int j = 0; j < WIDTH; j++) {
		// 		pros::c::screen_set_pen(0, 0, 0);
		// 		pros::c::screen_draw_pixel(i, j);
		// 	}
		// }
		pros::delay(50);
	}
}
