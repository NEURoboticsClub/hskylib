#ifndef UTILS_H
#define UTILS_H

#include "api.h"

uint16_t getInputExtremeForGearset(pros::motor_gearset_e gearset);

bool doubleEquals(double val1, double val2, double tolerance);

enum DriveStyle {
    ARCADE,
    TANK
};

// Experimental
enum PIDMode {
    DRIVING,
    TURNING,
    COMBINED,
    OFF
};

enum ExceptionCode {
    INVALID_ARGUMENT = 0
};

double scaleControllerInput(int x);
#endif