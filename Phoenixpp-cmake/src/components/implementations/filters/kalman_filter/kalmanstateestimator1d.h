#ifndef KALMANSTATEESTIMATOR1D_H
#define KALMANSTATEESTIMATOR1D_H

#include "kalmanfilter.h"
#include "roboime_time.h"

class KalmanStateEstimator1D
{
public:
    KalmanStateEstimator1D() = default;
    virtual ~KalmanStateEstimator1D() = default;
    KalmanStateEstimator1D(const Eigen::Vector2d &initialState, const Eigen::Matrix2d &initialCovariance,
                           double modelError, double measurementError, const float &timeStamp);

    void correction_measurementUpdate(const double &position);
    bool predict_timeUpdate(const RoboimeTime &timeStamp);

    [[nodiscard]] virtual const Eigen::Vector2d &get1DState() const; //(x,y,vx,vy)
    [[nodiscard]] virtual double getPosition() const;
    [[nodiscard]] double getVelocity() const;

    [[nodiscard]] virtual double getPositionEstimate(const RoboimeTime &time) const;
    [[nodiscard]] double getPositionUncertainty() const;
    [[nodiscard]] double getVelocityUncertainty() const;

    void setMeasurementError(double error);
    void setState(const Eigen::Vector2d &state);
    void setPosition(const double &position);
    void setVelocity(const double &velocity);
    void setCovariance(const Eigen::Matrix2d &covariance);

    [[nodiscard]] RoboimeTime lastUpdated() const;
    [[nodiscard]] Eigen::Matrix2d getCovariance() const;
    [[nodiscard]] double getInnovation() const;


protected:
    KalmanFilter<2,1> kalmanFilter1D;

private:
    void setTransitionMatrix(double dt);
    void setProcessNoiseFromRandomAcceleration(double dt);

    RoboimeTime lastUpdateTime;
    double modelError = 0.0;

};

#endif // KALMANSTATEESTIMATOR1D_H
