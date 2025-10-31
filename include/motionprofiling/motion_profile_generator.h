#ifndef MOTION_PROFILE_GENERATOR_H
#define MOTION_PROFILE_GENERATOR_H

#include "motion_profile.h"
#include "pose.h"
#include <vector>

/**
 * Generates a motion profile for a given set of parameters.
 */
class MotionProfileGenerator {
public:
    /**
     * Generates a motion profile based on the provided parameters.
     * 
     * @param waypoints An array of Pose objects representing the waypoints of the path.
     * @param maxVelocity The maximum velocity to be reached during the motion profile.
     * @param acceleration The acceleration to be used in the motion profile.
     * @return A MotionProfile object representing the generated motion profile.
     */
    static MotionProfile generateProfile(std::vector<Pose> waypoints, double maxVelocity, double acceleration);
};

#endif