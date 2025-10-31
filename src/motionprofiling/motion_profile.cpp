#include "motion_profile.h"
#include <cmath>

MotionProfile::MotionProfile(std::map<Pose, double> distanceMap,
        double totalDistance,
        double maxVelocity, 
        double endAccelerationDistance, 
        double startDecelerationDistance) {

    this->distanceMap = distanceMap;
    this->totalDistance = totalDistance;
    this->maxVelocity = maxVelocity;
    this->endAccelerationDistance = endAccelerationDistance;
    this->startDecelerationDistance = startDecelerationDistance;
}

double MotionProfile::getVelocityFromPosition(Pose pose) {
    /* Find the closest pose in the distance map */
    Pose closestPose;
    if (distanceMap.contains(pose)) {
        closestPose = pose;
    } else {
        double closestDistance = std::numeric_limits<double>::max();
        for (auto distancePair : distanceMap) {
            double dist = std::hypot(
                pose.x - distancePair.first.x,
                pose.y - distancePair.first.y);
            if (dist < closestDistance) {
                closestDistance = dist;
                closestPose = distancePair.first;
            }
        }
    }

    /* Determine velocity based on distance to target */
    double distanceAccumulated = distanceMap[closestPose];

    // Same for acceleration and deceleration distances
    double accelerationDistance = endAccelerationDistance;

    // Note: Using v / vmax = sqrt(d / dmax)

    if (distanceAccumulated <= endAccelerationDistance) {
        // Accelerating
        double velocity = maxVelocity * sqrt(distanceAccumulated / accelerationDistance);
        return std::min(velocity, maxVelocity);
    } else if (distanceAccumulated >= startDecelerationDistance) {
        // Decelerating
        double distanceToTarget = totalDistance - distanceAccumulated;
        double velocity = maxVelocity * sqrt(distanceToTarget / accelerationDistance);
        return std::min(velocity, maxVelocity);
    } else {
        // Cruising
        return maxVelocity;
    }
}