#ifndef KALMANSTATEESTIMATOR3D_H
#define KALMANSTATEESTIMATOR3D_H

#include "kalmanfilter.h"
#include "roboime_time.h"


class kalmanStateEstimator3D
{
public:
    kalmanStateEstimator3D() = default;
    kalmanStateEstimator3D(const Eigen::Vector<double, 9> &initialState, const Eigen::Matrix<double, 9, 9> &initialCovariance, double modelError, double measurementError, const RoboimeTime &timeStamp);

    bool predict(const RoboimeTime &timeStamp);
    void update(const Eigen::Vector3d &position);

    [[nodiscard]] const Eigen::Vector<double, 9> &getState() const;
    [[nodiscard]] Eigen::Vector3d getPosition() const;
    [[nodiscard]] Eigen::Vector3d getVelocity() const;

    [[nodiscard]] Eigen::Vector3d getPositionEstimate(const RoboimeTime &RoboimeTime) const;

    [[nodiscard]] Eigen::Vector3d getPositionUncertainty() const;
    [[nodiscard]] Eigen::Vector3d getAccelerationUncertainty() const;
    [[nodiscard]] Eigen::Vector3d getVelocityUncertainty() const;


    void setMeasurementError(double error);

    void setState(const Eigen::Vector<double, 9> &state);

    void setPosition(const Eigen::Vector3d &position);
    void setVelocity(const Eigen::Vector3d &velocity);
    void setAcceleration(const Eigen::Vector2d &acceleration);

    void setCovariance(const Eigen::Matrix<double, 9, 9> &covariance);

    [[nodiscard]] RoboimeTime lastUpdated() const;
    [[nodiscard]] Eigen::Matrix<double, 9, 9> getCovariance() const;
    [[nodiscard]] Eigen::Vector3d getInnovation() const;
    void addUncertainty(double posUncertainty, double velUncertainty, double accUncertainty);

private:
    void setTransitionMatrix(double dt);
    void setProcessNoiseFromRandomAcceleration(double dt);

    RoboimeTime lastUpdateTime;
    KalmanFilter<9,3> filter;
    double modelError = 0.0;
};

#endif // KALMANSTATEESTIMATOR3D_H
