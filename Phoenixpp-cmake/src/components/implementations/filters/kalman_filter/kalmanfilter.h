#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include <mutex>
#include <atomic>
#include <Eigen/Dense>
#include "../../../base_component.h"
#include "../../../messages/environment.h"
#include "../../../messages/raw_environment.h"

template<int stateVectorDimension, int outputVectorDimension>
class KalmanFilter : public TBaseComponent<Environment>
{
public:
    typedef Eigen::Matrix<double, stateVectorDimension,
                          stateVectorDimension> stateMatrix;
    typedef Eigen::Matrix<double, outputVectorDimension,
                          stateVectorDimension> outputMatrix;
    typedef Eigen::Matrix<double, outputVectorDimension,
                          outputVectorDimension> observationNoiseCovariance;
    typedef Eigen::Matrix<double, stateVectorDimension,
                          outputVectorDimension> inputMatrix;
    typedef Eigen::Matrix<double, stateVectorDimension, 1> stateVector;
    typedef Eigen::Matrix<double, outputVectorDimension, 1> outputVector;

private:
    stateVector vector_x;
    stateMatrix covarianceMatrix_P; //Accuracy of the state estimate

public:
    stateMatrix matrix_Phi;
    outputMatrix matrix_H;
    stateMatrix covarianceMatrix_Q;
    observationNoiseCovariance covarianceMatrix_R;
    stateMatrix matrix_B; //state transition jacobian

    outputVector vector_measurementStateError;

    KalmanFilter(atomic<bool>& stop, double fps);

    void predict_timeUpdate();
    void predict_timeUpdate(const stateVector &controlVector_u);
    void correction_measurementUpdate(const outputVector &cameraMeasurementVector_y);

    const stateVector &getStateVector() const;
    const stateMatrix &getCovarianceMatrix_P() const;
    void setStateVector(const stateVector& newVector_x);
    void setCovarianceMatrix_P(const stateMatrix &newCovarianceMatrix_P);
    Environment update(Environment environment) override;
    void start() override;
    ~KalmanFilter();
};

#endif
