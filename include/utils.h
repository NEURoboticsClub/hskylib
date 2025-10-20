#ifndef UTILS_H
#define UTILS_H

#include "api.h"

/**
 * Returns the absolute value of the input limits for the given gearset.
 */
uint16_t getInputExtremeForGearset(pros::motor_gearset_e gearset);

/**
 * Equality comparison between two doubles.
 */
bool doubleEquals(double val1, double val2, double tolerance);

/**
 * A control configuration for a drivebase.
 *
 * ARCADE: The robot moves left, right, forward, and backward in relation to
 * the state of the left joystick
 * TANK: The robot moves forward and backward in relation to the y-axis value of
 * the left joystick and moves left and right in relation to the x-axis value of
 * the right joystick
 */
enum DriveStyle { ARCADE, TANK };

// Experimental
enum PIDMode { DRIVING, TURNING, COMBINED, OFF };

/**
 * An error value representing a particular kind of error.
 */
enum ExceptionCode { INVALID_ARGUMENT = 0 };

/**
 * Scales controller input on an exponential function to provide better fine
 * control over the robot's lateral movement.
 */
double scaleControllerInput(int x);

/**
 * Takes a filename as input and returns the contents of the file as a long
 * string that can be managed Basically a Wrapper for the PROS Filereading
 * operation filenames should start with a \usd\ file prefix Note that reading
 * with bad filename will return an empty string, and that methods using this
 * method, will use an empty string as an error conditionas consequence.
 */
std::string readFile(std::string fileName, int bufferLength);

#endif
