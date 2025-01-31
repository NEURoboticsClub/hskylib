#include "PIDController.h"


PIDController::PIDController(double kp, double ki, double kd)
    : kp_(kp), ki_(ki), kd_(kd), prev_error_(0.0), integral_(0.0), prev_time_(std::chrono::steady_clock::now()) {}


PIDController::~PIDController() {}


double PIDController::compute(double setpoint, double current_value) {
    double error = setpoint - current_value;

    auto current_time = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = current_time - prev_time_;
    double dt = elapsed.count();

    double Pout = kp_ * error;

    integral_ += error * dt;
    double Iout = ki_ * integral_;

    double derivative = (error - prev_error_) / dt;
    double Dout = kd_ * derivative;

    prev_error_ = error;
    prev_time_ = current_time;

    return Pout + Iout + Dout;
}


void PIDController::setKp(double kp) { kp_ = kp; }

void PIDController::setKi(double ki) { ki_ = ki; }

void PIDController::setKd(double kd) { kd_ = kd; }


double PIDController::getKp() const { return kp_; }

double PIDController::getKi() const { return ki_; }

double PIDController::getKd() const { return kd_; }
