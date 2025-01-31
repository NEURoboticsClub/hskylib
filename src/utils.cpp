#include "utils.h"

uint16_t getInputExtremeForGearset(pros::motor_gearset_e gearset) {
    switch(gearset) {
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
    return false;
}