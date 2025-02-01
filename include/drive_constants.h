#ifndef DRIVE_CONSTANTS_H
#define DRIVE_CONSTANTS_H

namespace DriveConstants {
    // Physical robot constants
    constexpr double WHEEL_DIAMETER = 4.125;  // inches
    constexpr double WHEEL_CIRCUMFERENCE = WHEEL_DIAMETER * M_PI;
    constexpr double TRACK_WIDTH = 11.5;    // distance between wheels in inches
    constexpr double TICKS_PER_REV = 360; // encoder ticks per revolution
    
    // PID Constants for driving straight
    constexpr double DRIVE_KP = 1; 
    constexpr double DRIVE_KI = 0.0;
    constexpr double DRIVE_KD = 0.0;
    
    // PID Constants for turning
    constexpr double TURN_KP = 0.8;
    constexpr double TURN_KI = 0.001;
    constexpr double TURN_KD = 0.2;
    
    // Tolerances
    constexpr double DRIVE_TOLERANCE = 0;  // inches
    constexpr double TURN_TOLERANCE = 0;   // degrees
    
    // Movement limits
    constexpr int MAX_DRIVE_VELOCITY = 127;  // velocity units
    constexpr int MAX_TURN_VELOCITY = 127;   // velocity units
}

#endif 