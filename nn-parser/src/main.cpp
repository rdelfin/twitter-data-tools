//
// Created by rdelfin on 12/7/15.
//

#include <neural-network/NeuralNetwork.h>

#include <armadillo>
#include <functional>

int main(int argc, char* argv[]) {
    NeuralNetwork network([](const arma::mat& in)-> arma::mat{
        return 1.0 / (1.0 + arma::exp(-1.0 * in));
    });

    network(arma::mat(4, 5, arma::fill::randn));

    return 0;
}