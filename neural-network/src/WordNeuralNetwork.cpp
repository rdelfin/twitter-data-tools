//
// Created by rdelfin on 12/8/15.
//

#include <armadillo>
#include "neural-network/WordNeuralNetwork.h"

WordNeuralNetwork::WordNeuralNetwork(unsigned inputs, unsigned outputs, unsigned hidden, ActivationFunction func)
        : activation(func), inputN(inputs), outputN(outputs), hiddenN(hidden),
          theta1(inputs + 1, hidden, arma::fill::randn), theta2(hidden + 1, outputs, arma::fill::randn) {
}

void WordNeuralNetwork::setX(const arma::mat &x) {
    if(x.n_cols != inputN) {
        throw DimensionsException();
    }

    this->x = x;
}

arma::mat WordNeuralNetwork::operator()(const arma::mat& in) {
    if(in.n_cols != inputN) {
        throw DimensionsException();
    }

    arma::mat a1 = arma::join_horiz(arma::mat(in.n_rows, 1, arma::fill::ones), in);

    arma::mat s2 = a1 * theta1;
    arma::mat a2 = activation(s2);
    a2 = arma::join_horiz(arma::mat(in.n_rows, 1, arma::fill::ones), a2);

    arma::mat s3 = a2 * theta2;

    return s3;
}


double WordNeuralNetwork::value(const cppoptlib::Vector <double> &x) {
    return -1;
}
