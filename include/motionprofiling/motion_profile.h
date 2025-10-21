/**
 * Represents a motion profile for a path
 */
class MotionProfile {
public:
    /**
     * Constructs a MotionProfile with specified parameters.
     * 
     * @param distanceMap A map of Pose objects to their corresponding accumulated distances.
     * @param maxVelocity The maximum velocity to be reached during the motion profile.
     * @param endAccelerationDistance The distance along the path where initial acceleration stops.
     * @param startDecelerationDistance The distance along the path where deceleration begins.
     */
    MotionProfile(std::map<Pose, double> distanceMap,
            double totalDistance,
            double maxVelocity, 
            double endAccelerationDistance, 
            double startDecelerationDistance);
    
    /**
     * Gets the target velocity at a given position
     * 
     * @param pose The Pose object representing the current position.
     * @return The target velocity at the given position.
     */
    double getVelocityFromPosition(Pose pose);

private:
    std::map<Pose, double> distanceMap;
    double totalDistance;
    double maxVelocity;
    double endAccelerationDistance;
    double startDecelerationDistance;
};