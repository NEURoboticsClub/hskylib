#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <chrono>

class PIDController {
public:

    PIDController(double kp, double ki, double kd);

    virtual ~PIDController();


    virtual double compute(double setpoint, double current_value);


    void setKp(double kp);
    void setKi(double ki);
    void setKd(double kd);


    double getKp() const;
    double getKi() const;
    double getKd() const;

protected:

    double kp_;
    double ki_;
    double kd_;


    double prev_error_;
    double integral_;
    std::chrono::steady_clock::time_point prev_time_;
};

#endif
