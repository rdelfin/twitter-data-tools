//
// Created by rdelfin on 12/8/15.
//

#include "neural-network/WordNeuralNetwork.h"

WordNeuralNetwork::WordNeuralNetwork(unsigned inputs, unsigned outputs, unsigned hidden, ActivationFunction func)
        : activation(func), inputN(inputs), outputN(outputs), hiddenN(hidden),
          theta1(Eigen::MatrixXd::Random(inputs + 1, hidden)), theta2(Eigen::MatrixXd::Random(hidden + 1, outputs)) {

}

void WordNeuralNetwork::setX(const Eigen::MatrixXd &x) {
    if(x.cols() != inputN) {
        throw DimensionsException();
    }

    this->x = x;
}

Eigen::MatrixXd WordNeuralNetwork::operator()(const Eigen::MatrixXd& in) {
    if(in.cols() != inputN) {
        throw DimensionsException();
    }



    Eigen::MatrixXd a1;
    a1.resize(in.rows(), in.cols() + 1);
    a1 << Eigen::MatrixXd::Constant(in.rows(), 1, 1), in;

    Eigen::MatrixXd s2 = a1 * theta1;
    Eigen::MatrixXd tempA2 = activation(s2);


    Eigen::MatrixXd a2;
    a2.resize(tempA2.rows(), tempA2.cols() + 1);
    a2 << Eigen::MatrixXd::Constant(tempA2.rows(), 1, 1), tempA2;
    Eigen::MatrixXd s3 = a2 * theta2;

    return s3;
}

double WordNeuralNetwork::value(const cppoptlib::Vector<double> &x) {
    double num = x(5);
    return -1;
}
