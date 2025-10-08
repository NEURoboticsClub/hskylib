#include "button.h"

Button::Button(int x, int y, int width, int height, pros::Color border,
			   pros::Color fill, std::string label)
	: x(x),
	  y(y),
	  width(width),
	  height(height),
	  borderColor(border),
	  fillColor(fill),
	  label(label),
	  lastPressed(false) {}

void Button::draw() {
	
	pros::screen::set_pen(borderColor);
	pros::screen::draw_rect(x, y, x + width, y + height);
	pros::screen::set_pen(fillColor);
	pros::screen::fill_rect(x + 2, y + 2, x + width - 2, y + height - 2);
	

	int char_width = 9;
	int text_height = 14;

	if (!label.empty()) {
		pros::screen::set_pen(pros::Color::white);
		pros::screen::print(pros::E_TEXT_MEDIUM,
			(x + width / 2) - (label.length() * char_width) / 2,
			y + (height - text_height) / 2,
			"%s", label.c_str());
	}


}

bool Button::statusInBounds(pros::screen_touch_status_s_t status) {
	return (status.touch_status == pros::E_TOUCH_PRESSED ||
			status.touch_status == pros::E_TOUCH_HELD) &&
		   (status.x >= x && status.x <= x + width && status.y >= y &&
			status.y <= y + height);
}

bool Button::isPressed(pros::screen_touch_status_s_t status) {
	bool in_bounds = statusInBounds(status);
	bool return_value = in_bounds && (lastPressed != in_bounds);
	lastPressed = in_bounds;
	return return_value;
}

void Button::setBorderColor(pros::Color borderColor) {
	this->borderColor = borderColor;
}

void Button::setFillColor(pros::Color fillColor) {
	this->fillColor = fillColor;
}

void Button::setLabel(const std::string &label) { this->label = label; }