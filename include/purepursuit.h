#ifndef PURE_PURSUIT_H
#define PURE_PURSUIT_H

#include <vector>
#include <string>
#include <memory>
#include <atomic>
#include <thread>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>

#include "tank_drive.h" 
#include "odometry.h"     // needs to provide pose {x, y, theta}

// Structure for a single path point
struct PathPoint {
    double x;
    double y;
    double heading;
    double velocity;
};

// Asynchronous Adaptive Pure Pursuit Controller
class AsyncAdaptivePurePursuitController {
public:
    AsyncAdaptivePurePursuitController(TankDrive* drive, std::shared_ptr<Odometry> odom);
    ~AsyncAdaptivePurePursuitController();

    // Path management
    void setPath(const std::vector<PathPoint>& newPath);
    void setPathFromCSV(const std::string& filename);

    // Control
    void start();
    void stop();
    bool isRunning() const;

private:
    TankDrive* drive;
    std::shared_ptr<Odometry> odom;
    std::vector<PathPoint> path;

    std::atomic<bool> running;
    std::thread controlThread;

    // Internal helpers 
    void runLoop();
    std::vector<PathPoint> loadPathFromCSV(const std::string& filename);
    PathPoint findLookaheadPoint(const Pose& robotPose, double lookaheadDist);
    double computeCurvature(const Pose& robotPose, const PathPoint& target);
    double clamp(double value, double minVal, double maxVal);
};

#endif