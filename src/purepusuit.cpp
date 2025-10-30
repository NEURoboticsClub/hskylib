#include "AsyncAdaptivePurePursuitController.hpp"
#include <iostream>

AsyncAdaptivePurePursuitController::AsyncAdaptivePurePursuitController(TankDrive* drive, std::shared_ptr<Odometry> odom)
    : drive(drive), odom(odom) {}

AsyncAdaptivePurePursuitController::~AsyncAdaptivePurePursuitController() {
    stop();
}

void AsyncAdaptivePurePursuitController::setPath(const std::vector<PathPoint>& newPath) {
    path = newPath;
}

void AsyncAdaptivePurePursuitController::setPathFromCSV(const std::string& filename) {
    path = loadPathFromCSV(filename);
}

bool AsyncAdaptivePurePursuitController::isRunning() const {
    return running.load();
}

void AsyncAdaptivePurePursuitController::start() {
    if (running) return;
    running = true;
    controlThread = std::thread(&AsyncAdaptivePurePursuitController::runLoop, this);
}

void AsyncAdaptivePurePursuitController::stop() {
    running = false;
    if (controlThread.joinable()) controlThread.join();
}

std::vector<PathPoint> AsyncAdaptivePurePursuitController::loadPathFromCSV(const std::string& filename) {
    std::vector<PathPoint> path;
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "[PurePursuit] Failed to open CSV file: " << filename << std::endl;
        return path;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string xStr, yStr;

        if (!std::getline(ss, xStr, ',')) continue;
        if (!std::getline(ss, yStr, ',')) continue;

        double x = std::stod(xStr);
        double y = std::stod(yStr);

        path.push_back({x, y, 0.0, 0.0});
    }

    // Compute headings
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        double dx = path[i + 1].x - path[i].x;
        double dy = path[i + 1].y - path[i].y;
        path[i].heading = std::atan2(dy, dx);
    }

    // Assign velocities
    for (auto &p : path)
        p.velocity = 1.0;  // 1 m/s default, tune later

    std::cout << "[PurePursuit] Loaded path with " << path.size() << " points." << std::endl;
    return path;
}

PathPoint AsyncAdaptivePurePursuitController::findLookaheadPoint(const Pose& robotPose, double lookaheadDist) {
    if (path.empty()) return {0, 0, 0, 0};

    // Simple nearest-point + lookahead approach
    double minDist = 1e9;
    int nearestIdx = 0;

    for (int i = 0; i < static_cast<int>(path.size()); ++i) {
        double dx = path[i].x - robotPose.x;
        double dy = path[i].y - robotPose.y;
        double dist = std::sqrt(dx * dx + dy * dy);
        if (dist < minDist) {
            minDist = dist;
            nearestIdx = i;
        }
    }

    int lookaheadIdx = std::min(nearestIdx + 5, (int)path.size() - 1);
    return path[lookaheadIdx];
}

double AsyncAdaptivePurePursuitController::computeCurvature(const Pose& robotPose, const PathPoint& target) {
    double dx = target.x - robotPose.x;
    double dy = target.y - robotPose.y;
    double distance2 = dx * dx + dy * dy;
    double headingError = std::atan2(dy, dx) - robotPose.theta;
    return (2.0 * std::sin(headingError)) / std::sqrt(distance2);
}

double AsyncAdaptivePurePursuitController::clamp(double value, double minVal, double maxVal) {
    if (value < minVal) return minVal;
    if (value > maxVal) return maxVal;
    return value;
}

void AsyncAdaptivePurePursuitController::runLoop() {
    const double lookaheadDist = 0.25;  // tune this
    const double baseSpeed = 0.5;       // tune this
    const double trackWidth = 0.3;      // tune this

    std::cout << "[PurePursuit] Starting control loop..." << std::endl;

    while (running) {
        Pose pose = odom->getPose();
        PathPoint target = findLookaheadPoint(pose, lookaheadDist);

        double curvature = computeCurvature(pose, target);
        double leftVel = baseSpeed * (2.0 - curvature * trackWidth) / 2.0;
        double rightVel = baseSpeed * (2.0 + curvature * trackWidth) / 2.0;

        leftVel = clamp(leftVel, -1.0, 1.0);
        rightVel = clamp(rightVel, -1.0, 1.0);

        drive->tank(leftVel, rightVel);

        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    drive->tank(0, 0);
    std::cout << "[PurePursuit] Stopped." << std::endl;
}
🧭 Example usage
cpp
Copy code
#include "AsyncAdaptivePurePursuitController.hpp"

int main() {
    TankDrive drive; // your implementation
    auto odom = std::make_shared<Odometry>();

    AsyncAdaptivePurePursuitController purePursuit(&drive, odom);
    purePursuit.setPathFromCSV("/usd/test_path.csv");
    purePursuit.start();

    // Run for ~10 seconds
    pros::delay(10000);
    purePursuit.stop();
}