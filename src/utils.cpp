#include "utils.h"
#include "drive_constants.h"

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
    return fabs(val1 - val2) < tolerance;
}

double scaleControllerInput(int x) {
    if (abs(x) <= 5) {
        return 0;
    }

    double abs_x = abs(x);
    double result = (abs_x / x) * ((1.2 * pow(1.0356, abs_x)) - 1.2 + (0.2 * abs_x));

    return result;
}

double inchesToTicks(double inches) {
    return (inches / DriveConstants::WHEEL_CIRCUMFERENCE) * DriveConstants::TICKS_PER_REV;
}

double ticksToInches(double ticks) {
    return (ticks / DriveConstants::TICKS_PER_REV) * DriveConstants::WHEEL_CIRCUMFERENCE;
}

double degreesToTicks(double degrees) {
    double arcLength = (degrees / 360.0) * (DriveConstants::TRACK_WIDTH * M_PI);
    return inchesToTicks(arcLength);
}