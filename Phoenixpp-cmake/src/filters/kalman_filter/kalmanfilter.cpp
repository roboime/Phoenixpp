#include "kalmanfilter.h"

template<int stateVectorDimension, int outputVectorDimension>
KalmanFilter<stateVectorDimension, outputVectorDimension>::KalmanFilter() {
    matrix_Phi = stateMatrix::Identity();
    matrix_H = outputMatrix::Identity();
    covarianceMatrix_Q = stateMatrix::Zero();
    covarianceMatrix_R = observationNoiseCovariance::Zero();

    matrix_B = stateMatrix::Identity();
    vector_measurementStateError = outputVector::Zero();
}

template<int stateVectorDimension, int outputVectorDimension>
KalmanFilter<stateVectorDimension, outputVectorDimension>::KalmanFilter(const stateVector &x, const stateMatrix &P)
    : vector_x(x)
    , covarianceMatrix_P(P)
{
    matrix_Phi = stateMatrix::Identity();
    matrix_H = outputMatrix::Identity();
    covarianceMatrix_Q = stateMatrix::Zero();
    covarianceMatrix_R = observationNoiseCovariance::Zero();

    matrix_B = stateMatrix::Identity();
    vector_measurementStateError = outputVector::Zero();
}

template<int stateVectorDimension, int outputVectorDimension>
void KalmanFilter<stateVectorDimension, outputVectorDimension>::predict_timeUpdate() {
    vector_x = matrix_Phi * vector_x;
    covarianceMatrix_P = matrix_Phi * covarianceMatrix_P * matrix_Phi.transpose() + covarianceMatrix_Q;
}

template<int stateVectorDimension, int outputVectorDimension>
void KalmanFilter<stateVectorDimension, outputVectorDimension>::predict_timeUpdate(const stateVector &controlVector_u) {
    vector_x = matrix_Phi * vector_x + matrix_B * controlVector_u;
    covarianceMatrix_P = matrix_Phi * covarianceMatrix_P * matrix_Phi.transpose() + covarianceMatrix_Q;
}

template<int stateVectorDimension, int outputVectorDimension>
void KalmanFilter<stateVectorDimension, outputVectorDimension>::correction_measurementUpdate(const outputVector &cameraMeasurementVector_y) {
    vector_measurementStateError = cameraMeasurementVector_y - (matrix_Phi * vector_x);
    observationNoiseCovariance auxiliarMatrix = matrix_H * covarianceMatrix_P * matrix_H.transpose() + covarianceMatrix_R;
    inputMatrix kalmanGain = covarianceMatrix_P * matrix_H.transpose() * auxiliarMatrix.inverse();
    vector_x += kalmanGain * vector_measurementStateError;
    covarianceMatrix_P -= kalmanGain * matrix_H * covarianceMatrix_P;
}

template<int stateVectorDimension, int outputVectorDimension>
const typename KalmanFilter<stateVectorDimension, outputVectorDimension>::stateVector & KalmanFilter<stateVectorDimension, outputVectorDimension>::getStateVector() const {
    return vector_x;
}

template<int stateVectorDimension, int outputVectorDimension>
const typename KalmanFilter<stateVectorDimension, outputVectorDimension>::stateMatrix & KalmanFilter<stateVectorDimension, outputVectorDimension>::getCovarianceMatrix_P() const {
    return covarianceMatrix_P;
}

template<int stateVectorDimension, int outputVectorDimension>
void KalmanFilter<stateVectorDimension, outputVectorDimension>::setStateVector(const stateVector& newVector_x) {
    vector_x = newVector_x;
}

template<int stateVectorDimension, int outputVectorDimension>
void KalmanFilter<stateVectorDimension, outputVectorDimension>::setCovarianceMatrix_P(const stateMatrix &newCovarianceMatrix_P) {
    covarianceMatrix_P = newCovarianceMatrix_P;
}
