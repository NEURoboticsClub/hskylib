#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

#include "pose.h"
#include <cmath>

/**
 * A PID loop.
 */
template <typename T>
class PIDController {
    public:

        PIDController(double kp, double ki, double kd);

        // Compute and return the updated PID value
        double compute(T setpoint, T current_value);
        void reset();

        void setKp(double kp);
        void setKi(double ki);
        void setKd(double kd);

        double getKp() const;
        double getKi() const;
        double getKd() const;

    protected:

        // Multipliers for the proportional, integral, and derivative values, respectively.
        double kp_;
        double ki_;
        double kd_;

        double prev_error_;
        double integral_;
};

#endif
