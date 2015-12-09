//
// Created by rdelfin on 12/7/15.
//

#include <neural-network/WordNeuralNetwork.h>

#include <armadillo>
#include <functional>

int main(int argc, char* argv[]) {
    WordNeuralNetwork network(5, 3, 1, [](const arma::mat& in)-> arma::mat{
        return 1.0 / (1.0 + arma::exp(-1.0 * in));
    });

    arma::mat in = arma::mat(4, 5, arma::fill::randn);
    arma::mat out = network(in);
    in.impl_print("in = ");
    out.impl_print("NN(in) =");

    return 0;
}