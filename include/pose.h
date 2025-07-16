#ifndef POSE
#define POSE

/**
 * A position on the field. Values are absolute, not relative to the field.
 */
struct Pose {
	double x;
	double y;
	double theta;
};

#endif