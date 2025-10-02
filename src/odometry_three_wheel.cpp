#include "odometry_three_wheel.h"

#include "utils.h"

OdometryThreeWheel::OdometryThreeWheel(int8_t leftEncoderPort,
									   int8_t rightEncoderPort,
									   int8_t centerEncoderPort, double sL,
									   double sR, double sS)
	: Odometry(),
	  sL(sL),
	  sR(sR),
	  sS(sS),
	  leftEncoder(leftEncoderPort),
	  rightEncoder(rightEncoderPort),
	  centerEncoder(centerEncoderPort) {
	leftEncoder.reset_position();
	rightEncoder.reset_position();
	centerEncoder.reset_position();
	leftEncoderLastPos = 0;
	rightEncoderLastPos = 0;
	centerEncoderLastPos = 0;
}

void OdometryThreeWheel::reset() {
	Odometry::reset();

	leftEncoder.reset_position();
	rightEncoder.reset_position();
	centerEncoder.reset_position();
	leftEncoderLastPos = 0;
	rightEncoderLastPos = 0;
	centerEncoderLastPos = 0;
}

void OdometryThreeWheel::updatePose() {
	uint32_t leftEncoderNewPos = static_cast<uint32_t>(leftEncoder.get_position());
	uint32_t rightEncoderNewPos = static_cast<uint32_t>(rightEncoder.get_position());
	uint32_t centerEncoderNewPos = static_cast<uint32_t>(centerEncoder.get_position());
	double dL =
		static_cast<double>((((double)leftEncoderNewPos - (double)leftEncoderLastPos) / 36000.0) *
		6.28318);
	double dR =
		static_cast<double>((((double)rightEncoderNewPos - (double)rightEncoderLastPos) / 36000.0) *
		6.28318);
	double dC = static_cast<double>((((double)centerEncoderNewPos - (double)centerEncoderLastPos) /
				 36000.0) * 6.28318);
	double deltaThetaRad = static_cast<double>((dL - dR) / (sL + sR));

	double localOffsetX;
	double localOffsetY;

	if (doubleEquals(deltaThetaRad, 0.0, 0.01)) {
		localOffsetX = dC;
		localOffsetY = dR;
	} else {
		localOffsetX =
			(2.0 * sin(deltaThetaRad / 2.0) * (dC / deltaThetaRad) + sS);
		localOffsetY = (dR / deltaThetaRad) + sR;
	}

	double thetaM = static_cast<double>(currentPose->theta + (deltaThetaRad / 2.0));

	double dX = static_cast<double>((localOffsetX * cos(thetaM)) - (localOffsetY * sin(thetaM)));
	double dY = static_cast<double>((localOffsetX * sin(thetaM)) + (localOffsetY * cos(thetaM)));

	double x = static_cast<double>(currentPose->x + dX);
	double y = static_cast<double>(currentPose->y + dY);
	double theta = static_cast<double>(currentPose->theta + deltaThetaRad);

	currentPose->x = x;
	currentPose->y = y;
	currentPose->theta = theta;

	leftEncoderLastPos = leftEncoderNewPos;
	rightEncoderLastPos = rightEncoderNewPos;
	centerEncoderLastPos = centerEncoderNewPos;
}