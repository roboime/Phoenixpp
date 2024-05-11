#include "kalmanstateestimator1d.h"

KalmanStateEstimator1D::KalmanStateEstimator1D(const Eigen::Vector2d &initialState, const Eigen::Matrix2d &initialCovariance,
                                               double modelError, double measurementError, const float &timeStamp)
    : kalmanFilter1D{initialState, initialCovariance}
    , modelError{modelError}
{
    kalmanFilter1D.covarianceMatrix_R(0, 0) = measurementError;
}

void KalmanStateEstimator1D::timeUpdate(const double &position){
    kalmanFilter1D.predict_timeUpdate()
}
