#ifndef KALMANSTATEESTIMATOR1D_H
#define KALMANSTATEESTIMATOR1D_H

#include "kalmanfilter.h"

class KalmanStateEstimator1D
{
public:
    KalmanStateEstimator1D();

    KalmanStateEstimator1D(const Eigen::Vector2d &initialState, const Eigen::Matrix2d &initialCovariance,
                           double modelError, double measurementError, const float &timeStamp);
private:
    KalmanFilter<2,1> kalmanFilter1D;
    double modelError = 0.0;

};

#endif // KALMANSTATEESTIMATOR1D_H
