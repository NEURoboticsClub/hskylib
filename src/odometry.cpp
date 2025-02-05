#include "odometry.h"

Odometry::Odometry(){
    currentPose.x = 0.0;
    currentPose.y = 0.0;
    currentPose.theta = 0.0;
}

void Odometry::init() {
    pros::Task task([this] { runOdometry(); });
}

void Odometry::reset() {
    currentPose.x = 0.0;
    currentPose.y = 0.0;
    currentPose.theta = 0.0;
}

Pose Odometry::getPose(){
    return currentPose;
}

void Odometry::setPose(Pose newPose) {
    currentPose.x = newPose.x;
    currentPose.y = newPose.y;
    currentPose.theta = newPose.theta;
}

void Odometry::updatePose() {
    
}

void Odometry::runOdometry() {
    while (true) {
        updatePose();
        pros::delay(20);
    }
}