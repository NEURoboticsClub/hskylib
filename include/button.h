#pragma once
#include <string>
#include "pros/apix.h"

class Button {
  private:
	int x, y, width, height;
	pros::Color borderColor;
	pros::Color fillColor;
	std::string label;
	bool lastPressed;
	bool statusInBounds(pros::screen_touch_status_s_t status);

  public:
	Button(int x, int y, int width, int height,
		   pros::Color border = pros::Color::black,
		   pros::Color fill = pros::Color::white, std::string label = "");

	void draw();
	bool isPressed(pros::screen_touch_status_s_t status);

	void setBorderColor(pros::Color borderColor);
	void setFillColor(pros::Color fillColor);
	void setLabel(const std::string &label);
};