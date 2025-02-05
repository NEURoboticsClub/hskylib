#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include <chrono>

class PIDController {
public:

    PIDController(double kp, double ki, double kd);

    double compute(double setpoint, double current_value);
    void reset();

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
};

#endif
