#ifndef UTILS_H
#define UTILS_H

#include "api.h"

uint16_t getInputExtremeForGearset(pros::motor_gearset_e gearset);

bool doubleEquals(double val1, double val2, double tolerance);

#endif