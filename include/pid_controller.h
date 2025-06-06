#ifndef INCLUDE_PID_CONTROLLER_H_
#define INCLUDE_PID_CONTROLLER_H_

/**
 * @brief PID Controller Class
 */
template <typename T>
class PIDController {
 public:
    /**
     * @brief Create new PID controller
     * @param kp Proportional gain
     * @param ki Integral gain
     * @param kd Derivative gain
     */
    PIDController(double kp, double ki, double kd);

    /**
     * @brief Computes the output of the controller to a given ```setpoint``` from the ``current_value``.
     * @param setpoint The target set point to approach
     * @param current_value The current value (i.e current sensor value)
     */
    double compute(T setpoint, T current_value);

    /**
     * @brief Resets the previous error and integral value to zero.
     */
    void reset();

    /**
     * @brief Sets the proportional gain.
     * @param kp Proportional gain
     */
    void setKp(double kp);

    /**
     * @brief Sets the integral gain.
     * @param ki Integral gain
     */
    void setKi(double ki);

    /**
     * @brief Sets the derivative gain.
     * @param kd Derivative gain
     */
    void setKd(double kd);

    /**
     * @brief Gets the proportional gain.
     * @return Proportional gain
     */
    double getKp() const;

    /**
     * @brief Gets the integral gain.
     * @return Integral gain
     */
    double getKi() const;

    /**
     * @brief Gets the derivative gain.
     * @return Derivative gain
     */
    double getKd() const;

 protected:
    double kp_;
    double ki_;
    double kd_;

    double prev_error_;
    double integral_;
};

#endif  // INCLUDE_PID_CONTROLLER_H_
