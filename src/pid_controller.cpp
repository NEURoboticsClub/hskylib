#include "pid_controller.h"
#include "pose.h"
#include <cmath>

template <typename T>
PIDController<T>::PIDController(double kp, double ki, double kd)
    : kp_(kp), ki_(ki), kd_(kd), prev_error_(0.0), integral_(0.0) {}

template<>
double PIDController<Pose>::compute(Pose setpoint, Pose current_value) {
    double sign = 1.0;
    
    if (((setpoint.y - current_value.y) / (setpoint.x - current_value.x)) < 0.0) {
        sign = -1.0;
    }

    double error = sign * sqrt(pow((setpoint.x - current_value.x), 2.0) + pow((setpoint.y - current_value.y), 2.0));

    double proportional = kp_ * error;

    integral_ += ki_ * error;

    double derivative = kd_ * (error - prev_error_);

    prev_error_ = error;

    return proportional + integral_ + derivative;
}

template<>
double PIDController<double>::compute(double setpoint, double current_value) {
    double error = setpoint - current_value;

    double proportional = kp_ * error;

    integral_ += ki_ * error;

    double derivative = kd_ * (error - prev_error_);

    prev_error_ = error;

    return proportional + integral_ + derivative;
}

template <typename T>
void PIDController<T>::reset() {
    prev_error_ = 0.0;
    integral_ = 0.0;
}

template <typename T>
void PIDController<T>::setKp(double kp) { kp_ = kp; }

template <typename T>
void PIDController<T>::setKi(double ki) { ki_ = ki; }

template <typename T>
void PIDController<T>::setKd(double kd) { kd_ = kd; }

template <typename T>
double PIDController<T>::getKp() const { return kp_; }

template <typename T>
double PIDController<T>::getKi() const { return ki_; }

template <typename T>
double PIDController<T>::getKd() const { return kd_; }

template class PIDController<Pose>;
template class PIDController<double>;