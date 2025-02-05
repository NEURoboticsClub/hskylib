#include "pid_controller.h"

PIDController::PIDController(double kp, double ki, double kd)
    : kp_(kp), ki_(ki), kd_(kd), prev_error_(0.0), integral_(0.0) {}


double PIDController::compute(double setpoint, double current_value) {
    double error = setpoint - current_value;

    double proportional = kp_ * error;

    integral_ += ki_ * error;

    double derivative = kd_ * (error - prev_error_);

    prev_error_ = error;

    return proportional + integral_ + derivative;
}

void PIDController::reset() {
    prev_error_ = 0.0;
    integral_ = 0.0;
}

void PIDController::setKp(double kp) { kp_ = kp; }

void PIDController::setKi(double ki) { ki_ = ki; }

void PIDController::setKd(double kd) { kd_ = kd; }


double PIDController::getKp() const { return kp_; }

double PIDController::getKi() const { return ki_; }

double PIDController::getKd() const { return kd_; }