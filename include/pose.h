#ifndef POSE
#define POSE

#include <tuple>

/**
 * A position on the field. Values are absolute, not relative to the field.
 */
struct Pose {
	double x;
	double y;
	double theta;
};

/**
 * Comparison operator for Pose to enable use as a map key.
 * Compares lexicographically by x, then y, then theta.
 */
inline bool operator<(const Pose &a, const Pose &b) {
	return std::tie(a.x, a.y, a.theta) < std::tie(b.x, b.y, b.theta);
}

#endif