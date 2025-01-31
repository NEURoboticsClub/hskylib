#include "odometry_base.h"

OdometryBase::OdometryBase(){
    *currentPosition[0] = 0.0;
    *currentPosition[1] = 0.0;
    *currentPosition[2] = 0.0;
}

void OdometryBase::init() {
}

void OdometryBase::reset() {
    *currentPosition[0] = 0.0;
    *currentPosition[1] = 0.0;
    *currentPosition[2] = 0.0;
}

void OdometryBase::getPosition(double* pos[3]){
    for (uint8_t i = 0; i < 3; i++) {
        *pos[i] = *currentPosition[i];
    }
}

void OdometryBase::setPosition(double* pos[3]) {
    for (uint8_t i = 0; i < 3; i++) {
        *currentPosition[i] = *pos[i];
    }
}