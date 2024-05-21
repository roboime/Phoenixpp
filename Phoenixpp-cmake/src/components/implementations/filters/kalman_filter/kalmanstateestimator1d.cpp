#include "kalmanstateestimator1d.h"

KalmanStateEstimator1D::KalmanStateEstimator1D(const Eigen::Vector2d &initialState, const Eigen::Matrix2d &initialCovariance,
                                               double modelError, double measurementError, const float &timeStamp)
    : kalmanFilter1D{initialState, initialCovariance}
    , modelError{modelError}
{
    kalmanFilter1D.covariance_R(0, 0) = measurementError;
}

bool KalmanStateEstimator1D::predict_timeUpdate(const RoboimeTime &timeStamp)
{
    double dt = (timeStamp - lastUpdateTime).asSeconds();
    if (dt < 0){
        return dt == 0.0;
    }
    lastUpdateTime = timeStamp;
    setTransitionMatrix(dt);
    setProcessNoiseFromRandomAcceleration(dt);
    kalmanFilter1D.predict_timeUpdate();
    return true;
}


void KalmanStateEstimator1D::correction_measurementUpdate(const double &position){
    kalmanFilter1D.correction_measurementUpdate(Eigen::Matrix<double, 1, 1>(position));
}

double KalmanStateEstimator1D::getPositionUncertainty() const
{
    return sqrt(kalmanFilter1D.getCovarianceMatrix_P()(0, 0));
}

double KalmanStateEstimator1D::getVelocityUncertainty() const
{
    return sqrt(kalmanFilter1D.getCovarianceMatrix_P()(1, 1));
}

void KalmanStateEstimator1D::setMeasurementError(double error) {
    kalmanFilter1D.covariance_R(0, 0) = error;
}

void KalmanStateEstimator1D::setTransitionMatrix(double dt) {
    kalmanFilter1D.Phi(0, 1) = dt;
}
void KalmanStateEstimator1D::setProcessNoiseFromRandomAcceleration(double dt) {
    double sigmaSq = modelError * modelError;

    // Random gaussian distributed with variance sigmaSq
    double dt3 = (1.0 / 3.0) * dt * dt * dt * sigmaSq;
    double dt2 = (1.0 / 2.0) * dt * dt * sigmaSq;
    double dt1 = dt * sigmaSq;
    
    kalmanFilter1D.covariance_Q(0, 0) = dt3;
    kalmanFilter1D.covariance_Q(0, 1) = dt2;
    kalmanFilter1D.covariance_Q(1, 0) = dt2;
    kalmanFilter1D.covariance_Q(1, 1) = dt1;
}

const Eigen::Vector2d &KalmanStateEstimator1D::get1DState() const
{
    return kalmanFilter1D.getStateVector();
}

double KalmanStateEstimator1D::getPosition() const
{
    return kalmanFilter1D.getStateVector()[0];
}
double KalmanStateEstimator1D::getVelocity() const {
    return kalmanFilter1D.getStateVector()[1];
}
void KalmanStateEstimator1D::setState(const Eigen::Vector2d &state)
{
    kalmanFilter1D.setStateVector(state);
}
void KalmanStateEstimator1D::setPosition(const double &position)
{
    kalmanFilter1D.modifyStateVector(0, position);
}
void KalmanStateEstimator1D::setVelocity(const double &velocity)
{
    kalmanFilter1D.modifyStateVector(1, velocity);
}
double KalmanStateEstimator1D::getPositionEstimate(const RoboimeTime &time) const {
    // If query is trivial or somehow is bad, just return the latest estimate.
    if (time <= lastUpdateTime) {
        return getPosition();
    }
    // return linear extrapolation of current state.
    return getPosition() + (time - lastUpdateTime).asSeconds() * getVelocity();
}
void KalmanStateEstimator1D::setCovariance(const Eigen::Matrix2d &covariance)
{
    kalmanFilter1D.setCovarianceMatrix_P(covariance);
}
[[maybe_unused]] RoboimeTime KalmanStateEstimator1D::lastUpdated() const
{
    return lastUpdateTime;
}
Eigen::Matrix2d KalmanStateEstimator1D::getCovariance() const
{
    return kalmanFilter1D.getCovarianceMatrix_P();
}
double KalmanStateEstimator1D::getInnovation() const
{
    return kalmanFilter1D.vector_measurementStateError(0, 0);
}

