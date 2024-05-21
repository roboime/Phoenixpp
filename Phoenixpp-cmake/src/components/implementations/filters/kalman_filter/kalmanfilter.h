#ifndef KALMANFILTER_H
#define KALMANFILTER_H

#include <Eigen/Dense>
// #include "../../../messages/environment.h"
// #include "../../../messages/raw_environment.h"

template<int stateVectorDimension, int outputVectorDimension>
class KalmanFilter
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
    stateMatrix covariance_P; //Accuracy of the state estimate

public:
    stateMatrix Phi;
    outputMatrix H;
    stateMatrix covariance_Q;
    observationNoiseCovariance covariance_R;
    stateMatrix B; //state transition jacobian

    outputVector vector_measurementStateError;
    KalmanFilter(){
        Phi = stateMatrix::Identity();
        H = outputMatrix::Identity();
        covariance_Q = stateMatrix::Zero();
        covariance_R = observationNoiseCovariance::Zero();
        B = stateMatrix::Identity();
        vector_measurementStateError = outputVector::Zero();
    }
    explicit KalmanFilter(const stateVector &x, const stateMatrix & P)
        : vector_x(x)
        , covariance_P(P)
    {
        Phi = stateMatrix::Identity();
        H = outputMatrix::Identity();
        covariance_Q = stateMatrix::Zero();
        covariance_R = observationNoiseCovariance::Zero();

        B = stateMatrix::Identity();
        vector_measurementStateError = outputVector::Zero();
    }

    //Environment update(RawEnvironment raw_env){
    //}

    void predict_timeUpdate(){
        vector_x = Phi*vector_x;
        covariance_P = Phi*covariance_P*Phi.transpose() + covariance_Q;
    };

    void predict_timeUpdate(const stateVector &controlVector_u){
        vector_x = Phi*vector_x + B*controlVector_u;
        covariance_P = Phi*covariance_P*Phi.transpose() + covariance_Q;
    };

    void correction_measurementUpdate(const outputVector &cameraMeasurementVector_y){
        vector_measurementStateError = cameraMeasurementVector_y - (H*vector_x);
        observationNoiseCovariance S = H*covariance_P*H.transpose() + covariance_R;
        inputMatrix kalmanGain = covariance_P*H.transpose()*S.inverse();
        vector_x += kalmanGain*vector_measurementStateError;
        covariance_P -= kalmanGain*H*covariance_P;
    };
    const stateVector &getStateVector() const{
        return vector_x;
    }
    const stateMatrix &getCovarianceMatrix_P() const{
        return covariance_P;
    }

    void modifyStateVector(int index, double value)
    {
        vector_x(index) = value;
    }

    void setStateVector(const stateVector& newVector_x){
        vector_x = newVector_x;
    }
    void setCovarianceMatrix_P(const stateMatrix &newCovarianceMatrix_P){
        covariance_P = newCovarianceMatrix_P;
    }
};

#endif
