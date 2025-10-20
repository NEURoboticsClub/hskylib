#include "utils.h"

uint16_t getInputExtremeForGearset(pros::motor_gearset_e gearset) {
	switch (gearset) {
		case pros::E_MOTOR_GEAR_100:
			return 100;
		case pros::E_MOTOR_GEAR_200:
			return 200;
		case pros::E_MOTOR_GEAR_600:
			return 600;
		default:
			return 100;
	}
}

bool doubleEquals(double val1, double val2, double tolerance) {
	return fabs(val1 - val2) < tolerance;
}

double scaleControllerInput(int x) {
	if (abs(x) <= 5) {
		return 0;
	}

	double abs_x = abs(x);
	double result =
		(abs_x / x) * ((1.2 * pow(1.0356, abs_x)) - 1.2 + (0.2 * abs_x));

	return result;
}

std::string readFile(std::string filename, int bufferLength) {
	FILE *usd_file_read = fopen(filename.c_str(), "r");
	if (!usd_file_read) {
		return "";
	}

	char *buff = new char[bufferLength + 1];
	size_t bytes_read = fread(buff, 1, bufferLength, usd_file_read);
	buff[bytes_read] = '\0';

	std::string output_as_string(buff);
	delete[] buff;
	fclose(usd_file_read);
	return output_as_string;
}
