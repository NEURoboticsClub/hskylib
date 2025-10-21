#include "main.h"
#include <list>
#include <vector>

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
	int HEIGHT = 272;
	int WIDTH = 480;

	int squares = 5;
	int square_spacing = 25;
	int top_padding = 10;
	int bottom_padding = 40;
	int square_size = 65;
	int left_padding = (WIDTH - (squares  * (square_size + square_spacing)) + square_spacing) / 2;

    std::list<Button> auton_buttons = {};
	
	for (int i = 0; i < squares; i++) {
		auton_buttons.push_back(Button(left_padding + (square_spacing + square_size) * i, top_padding, square_size, square_size, pros::Color::white, pros::Color::black, std::to_string(i + 1)));
	}
	for (int i = 0; i < squares; i++) {
		auton_buttons.push_back(Button(left_padding + (square_spacing + square_size) * i, HEIGHT - bottom_padding - square_size, square_size, square_size, pros::Color::white, pros::Color::black, std::to_string(i + squares + 1)));
	}
    
	int color_seperation = square_spacing;
	int color_rect_height = square_size;
	int width = WIDTH / 2 - color_seperation / 2 - 20;

	Button redButton(left_padding, HEIGHT / 2 - color_rect_height / 2 - 15, width, color_rect_height, pros::Color::red, pros::Color::black, "Red");
	Button blueButton(left_padding + color_seperation / 2 + width, HEIGHT / 2 - color_rect_height / 2 - 15, width, color_rect_height, pros::Color::blue, pros::Color::black, "Blue");


	pros::screen_touch_status_s_t status;
	
	int auton_index = -1;
	int color_index = -1;

	std::list<Button> color_buttons = {redButton, blueButton};

	while(true) {
		status = pros::screen::touch_status();
	
		redButton.draw();
		if (redButton.isPressed(status)) {
			redButton.setFillColor(pros::Color::red);
		}
		blueButton.draw();
		if (blueButton.isPressed(status)) {
			blueButton.setFillColor(pros::Color::blue);
		}
		int j = 0;
		for (auto button = auton_buttons.begin(); button != auton_buttons.end(); ++button) {
			if (button -> isPressed(status)) {
				auton_index = j;
			} 
			else {
				button -> setFillColor(pros::Color::black);
			}
			j++;
		}
		j = 0;
		
		for (auto button = auton_buttons.begin(); button != auton_buttons.end(); ++button) {
			if (j == auton_index) {
				button -> setFillColor(pros::Color::grey);
			}
			j++;
		}

		for (auto button = auton_buttons.begin(); button != auton_buttons.end(); ++button) {
			button -> draw();
		}
		
		pros::delay(100);
	}
}