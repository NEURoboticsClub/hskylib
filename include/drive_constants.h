#ifndef DRIVE_CONSTANTS_H
#define DRIVE_CONSTANTS_H

namespace DriveConstants {
    // Physical robot constants
    constexpr double WHEEL_DIAMETER = 3.25;  // inches
    constexpr double WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * M_PI;
    constexpr double TRACK_WIDTH = 12.376;    // distance between wheels in inches
    constexpr double TICKS_PER_REV = 300.0*57.0/39.0; // encoder ticks per revolution
    
    // PID Constants for driving straight
    constexpr double DRIVE_KP = 2.0; 
    constexpr double DRIVE_KI = 0.0;
    constexpr double DRIVE_KD = 0.0;
    
    // PID Constants for turning
    constexpr double TURN_KP = 3.0;
    constexpr double TURN_KI = 0.0;
    constexpr double TURN_KD = 0.0;
    
    // Tolerances
    constexpr double DRIVE_TOLERANCE = 0.5;  // inches
    constexpr double TURN_TOLERANCE = 1.9;   // degrees
    
    // Movement limits
    constexpr int MAX_DRIVE_VELOCITY = 127;  // velocity units
    constexpr int MAX_TURN_VELOCITY = 127;   // velocity units
}

#endif 