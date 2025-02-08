#include "odometry.h"

Odometry::Odometry(){
    currentPose = new Pose(0.0,0.0,0.0);
}

void Odometry::init() {
    pros::Task task([this] { runOdometry(); });
}

void Odometry::reset() {
    currentPose->x = 0.0;
    currentPose->y = 0.0;
    currentPose->theta = 0.0;
}

void Odometry::getPose(Pose* pose) {
    pose->x = currentPose->x;
    pose->y = currentPose->y;
    pose->theta = currentPose->theta;
}

void Odometry::setPose(Pose* newPose) {
    currentPose->x = newPose->x;
    currentPose->y = newPose->y;
    currentPose->theta = newPose->theta;
}

void Odometry::updatePose() {
    
}

void Odometry::runOdometry() {
    while (true) {
        this->updatePose();
        pros::delay(20);
    }
}