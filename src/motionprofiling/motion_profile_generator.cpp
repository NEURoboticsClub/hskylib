#include "motion_profile_generator.h"
#include "motion_profile.h"
#include "pose.h"
#include "math.h"

MotionProfileGenerator::MotionProfileGenerator() {}

MotionProfile MotionProfileGenerator::generateProfile(Pose[] waypoints, double maxVelocity, double acceleration) {
    double totalDistance = 0.0;
    for (size_t i = 1; i < waypoints.size(); i++) {
        totalDistance += math::hypot(
            waypoints[i].x - waypoints[i-1].x, waypoints[i].y - waypoints[i-1].y);
    }

    double timeToAccelerate = maxVelocity / acceleration;

    double endAccelerationDistance = maxVelocity * timeToAccelerate / 2.0;
    double startDecelerationDistance = totalDistance - endAccelerationDistance;

    MotionProfile profile = MotionProfile(
        totalDistance, maxVelocity, endAccelerationDistance, startDecelerationDistance);

    return profile;
}