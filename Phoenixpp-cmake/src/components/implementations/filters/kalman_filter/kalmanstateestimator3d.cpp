#include "kalmanstateestimator3d.h"

bool kalmanStateEstimator3D::predict(const RoboimeTime &timeStamp) {
    double dt = (timeStamp - lastUpdateTime).asSeconds();
    if (dt <= 0) {
        return dt == 0.0;
    }
    lastUpdateTime = timeStamp;
    setTransitionMatrix(dt);
    setProcessNoiseFromRandomAcceleration(dt);
    filter.predict_timeUpdate();

    return true;
}
kalmanStateEstimator3D::kalmanStateEstimator3D(const Eigen::Vector<double, 9> &initialState, const Eigen::Matrix<double,9,9> &initialCovariance, double modelError, double measurementError, const RoboimeTime &timeStamp)
    : filter{initialState, initialCovariance}
    , lastUpdateTime{timeStamp}
    , modelError{modelError}
{
    filter.covariance_R(0, 0) = measurementError;
    filter.covariance_R(1, 1) = measurementError;
    filter.covariance_R(2, 2) = measurementError;
}
void kalmanStateEstimator3D::update(const Eigen::Vector3d &position)
{
    filter.correction_measurementUpdate(position);
}
Eigen::Vector3d kalmanStateEstimator3D::getPositionUncertainty() const {
    return filter.getCovarianceMatrix_P().diagonal().head<3>().array().sqrt();
    // Indices (0,0), (1,1), (2,2)
}
Eigen::Vector3d kalmanStateEstimator3D::getVelocityUncertainty() const {
    return filter.getCovarianceMatrix_P().diagonal().segment<3>(3).array().sqrt();
    // Indices (3,3), (4,4), (5,5)
}
Eigen::Vector3d kalmanStateEstimator3D::getAccelerationUncertainty() const {
    return filter.getCovarianceMatrix_P().diagonal().tail<3>().array().sqrt();
    // Indices (6,6), (7,7) and (8,8)
}
void kalmanStateEstimator3D::setMeasurementError(double error) {
    // filter.covariance_R(0, 0) = error;
    // filter.covariance_R(0, 1) = 0;
    // filter.covariance_R(1, 0) = 0;
    // filter.covariance_R(1, 1) = error;
    filter.covariance_R << error, 0, 0,
        0, error, 0,
        0, 0, error;
}
void kalmanStateEstimator3D::setTransitionMatrix(double dt) {
    filter.Phi.setIdentity();

    filter.Phi(0, 3) = dt;
    filter.Phi(0, 6) = dt * dt / 2;

    filter.Phi(1, 4) = dt;
    filter.Phi(1, 7) = dt * dt / 2;

    filter.Phi(2, 5) = dt;
    filter.Phi(2, 8) = dt * dt / 2;

    filter.Phi(3, 6) = dt;
    filter.Phi(4, 7) = dt;
    filter.Phi(5, 8) = dt;
}

void kalmanStateEstimator3D::setProcessNoiseFromRandomAcceleration(double dt) {
    // double q = modelError;

    // // Calculate elements of Q matrix
    // double dt2 = dt * dt;
    // double dt3 = dt * dt2;
    // double dt4 = dt2 * dt2;
    // double dt5 = dt2 * dt3;

    // filter.covariance_Q(0, 0) = q * dt5 / 20;
    // filter.covariance_Q(0, 3) = q * dt4 / 8;
    // filter.covariance_Q(0, 6) = q * dt3 / 6;

    // filter.covariance_Q(1, 1) = q * dt5 / 20;
    // filter.covariance_Q(1, 4) = q * dt4 / 8;
    // filter.covariance_Q(1, 7) = q * dt3 / 6;

    // filter.covariance_Q(2, 2) = q * dt5 / 20;
    // filter.covariance_Q(2, 5) = q * dt4 / 8;
    // filter.covariance_Q(2, 8) = q * dt3 / 6;

    // filter.covariance_Q(3, 0) = q * dt4 / 8;
    // filter.covariance_Q(3, 3) = q * dt3 / 3;
    // filter.covariance_Q(3, 6) = q * dt2 / 2;

    // filter.covariance_Q(4, 1) = q * dt4 / 8;
    // filter.covariance_Q(4, 4) = q * dt3 / 3;
    // filter.covariance_Q(4, 7) = q * dt2 / 2;

    // filter.covariance_Q(5, 2) = q * dt4 / 8;
    // filter.covariance_Q(5, 5) = q * dt3 / 3;
    // filter.covariance_Q(5, 8) = q * dt2 / 2;

    // filter.covariance_Q(6, 3) = q * dt3 / 6;
    // filter.covariance_Q(6, 6) = q * dt2 / 2;
    // filter.covariance_Q(6, 6) = q * dt;

    // filter.covariance_Q(7, 4) = q * dt3 / 6;
    // filter.covariance_Q(7, 7) = q * dt2 / 2;
    // filter.covariance_Q(7, 7) = q * dt;

    // filter.covariance_Q(8, 5) = q * dt3 / 6;
    // filter.covariance_Q(8, 8) = q * dt2 / 2;
    // filter.covariance_Q(8, 8) = q * dt;
    double q = modelError; //desvio padrão do processo

    double dt2 = dt * dt;
    double dt3 = dt * dt2;
    double dt4 = dt2 * dt2;
    double dt5 = dt2 * dt3;

    filter.covariance_Q << q*dt5/20, 0, 0, q*dt4/8, 0, 0, q*dt3/6, 0, 0,
                            0, q*dt5/20, 0, 0, q*dt4/8, 0, 0, q*dt3/6, 0,
                            0, 0, q*dt5/20, 0, 0, q*dt4/8, 0, 0, q*dt3/6,
                            q*dt4/8, 0, 0, q*dt3/3, 0, 0, q*dt2/2, 0, 0,
                            0, q*dt4/8, 0, 0, q*dt3/3, 0, 0, q*dt2/2, 0,
                            0, 0, q*dt4/8, 0, 0, q*dt3/3, 0, 0, q*dt2/2,
                            q*dt3/6, 0, 0, q*dt2/2, 0, 0, q*dt, 0, 0,
                            0, q*dt3/6, 0, 0, q*dt2/2, 0, 0, q*dt, 0,
                            0, 0, q*dt3/6, 0, 0, q*dt2/2, 0, 0, q*dt;
}

const Eigen::Vector<double, 9> &kalmanStateEstimator3D::getState() const
{
    return filter.getStateVector();
}
Eigen::Vector3d kalmanStateEstimator3D::getPosition() const
{
    return filter.getStateVector().block<3,1>(0,0);
}
Eigen::Vector3d kalmanStateEstimator3D::getVelocity() const
{
    return filter.getStateVector().block<3,1>(3,0);
}

void kalmanStateEstimator3D::setState(const Eigen::Vector<double, 9> &state)
{
    filter.setStateVector(state);
}
void kalmanStateEstimator3D::setPosition(const Eigen::Vector3d &position)
{
    filter.modifyStateVector(0, position.x());
    filter.modifyStateVector(1, position.y());
}
void kalmanStateEstimator3D::setVelocity(const Eigen::Vector3d &velocity) {
    filter.modifyStateVector(2, velocity.x());
    filter.modifyStateVector(3, velocity.y());
}
Eigen::Vector3d kalmanStateEstimator3D::getPositionEstimate(const RoboimeTime &time) const {
    // If query is trivial or somehow is bad, just return the current position
    if (time <= lastUpdateTime) {
        return getPosition();
    }
    // return linear extrapolation of current state.
    return getPosition() + (time - lastUpdateTime).asSeconds() * getVelocity();
}
void kalmanStateEstimator3D::setCovariance(const Eigen::Matrix<double, 9, 9> &covariance)
{
    filter.setCovarianceMatrix_P(covariance);
}
RoboimeTime kalmanStateEstimator3D::lastUpdated() const { return lastUpdateTime; }
Eigen::Matrix<double, 9, 9> kalmanStateEstimator3D::getCovariance() const
{
    return filter.getCovarianceMatrix_P();
}
Eigen::Vector3d kalmanStateEstimator3D::getInnovation() const { return filter.vector_measurementStateError; }
void kalmanStateEstimator3D::addUncertainty(double posUncertainty, double velUncertainty, double accUncertainty) {
    Eigen::Matrix<double, 9, 9> covariance = filter.getCovarianceMatrix_P();
    covariance(0, 0) += posUncertainty;
    covariance(1, 1) += posUncertainty;
    covariance(2, 2) += posUncertainty;
    covariance(3, 3) += velUncertainty;
    covariance(4, 4) += velUncertainty;
    covariance(5, 5) += velUncertainty;
    covariance(6, 6) += accUncertainty;

    filter.setCovarianceMatrix_P(covariance);
}
