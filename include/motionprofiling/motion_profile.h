/**
 * Represents a motion profile for a path
 */
class MotionProfile {
public:
    /**
     * Constructs a MotionProfile with specified parameters.
     * 
     * @param totalDistance The total distance to be covered by the motion profile. (Arc length)
     * @param maxVelocity The maximum velocity to be reached during the motion profile.
     * @param endAccelerationDistance The distance to target where initial acceleration stops.
     * @param startDecelerationDistance The distance to target where deceleration begins.
     */
    MotionProfile(double totalDistance, 
            double maxVelocity, 
            double endAccelerationDistance, 
            double startDecelerationDistance);
    
    /**
     * Gets the target velocity at a given position
     * 
     * @param position The current position
     * @return The target velocity at the given position.
     */
    double getVelocityFromPosition(double position);

};