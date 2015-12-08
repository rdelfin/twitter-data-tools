//
// Created by rdelfin on 12/7/15.
//

#include <neural-network/NeuralNetwork.h>
#include <armadillo>

NeuralNetwork::NeuralNetwork(ActivationFunction func)
    : activation(func) {

}

arma::vec NeuralNetwork::operator()(arma::mat in) {
    if(in.n_cols != inputN) {
        throw DimensionsException();
    }

    arma::mat l2 = in * theta1;
    arma::mat a2 = activation(l2);
    a2 = arma::join_horiz(arma::mat(in.n_rows, 1, arma::fill::ones), a2);

    arma::mat l3 = a2 * theta2;
    arma::mat a3 = activation(l3);

    return a3;
}
