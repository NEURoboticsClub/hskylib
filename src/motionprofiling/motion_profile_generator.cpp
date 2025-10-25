#include "motion_profile_generator.h"
#include "motion_profile.h"
#include "pose.h"
#include "math.h"

MotionProfile MotionProfileGenerator::generateProfile(std::vector<Pose> waypoints, double maxVelocity, double acceleration) {
    std::vector<double> distances = {0.0};
    double totalDistance = 0.0;
    for (size_t i = 1; i < waypoints.size(); i++) {
        totalDistance += std::hypot(
            waypoints[i].x - waypoints[i-1].x, waypoints[i].y - waypoints[i-1].y);
        distances.push_back(totalDistance);
    }

    std::map<Pose, double> distanceMap;
    for (size_t i = 0; i < waypoints.size(); i++) {
        distanceMap[waypoints[i]] = distances[i];
    }

    double timeToAccelerate = maxVelocity / acceleration;

    double endAccelerationDistance = maxVelocity * timeToAccelerate / 2.0;
    double startDecelerationDistance = totalDistance - endAccelerationDistance;

    MotionProfile profile = MotionProfile(distanceMap,
        totalDistance, maxVelocity, endAccelerationDistance, startDecelerationDistance);

    return profile;
}