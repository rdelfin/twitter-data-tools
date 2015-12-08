//
// Created by rdelfin on 12/7/15.
//

#ifndef TWITTER_DATA_TOOLS_NEURALNETWORK_H
#define TWITTER_DATA_TOOLS_NEURALNETWORK_H

#include <armadillo>
#include <exception>
#include <functional>

using ActivationFunction = std::function<arma::mat(const arma::mat &)>;

class NeuralNetwork {
public:
    NeuralNetwork(ActivationFunction func);
    arma::vec operator()(arma::mat in);

    ~NeuralNetwork() { }
private:
    arma::mat theta1;
    arma::mat theta2;

    long inputN;
    long outputN;

    ActivationFunction activation;
};


class DimensionsException : public std::exception {
public:
    DimensionsException() {}
    const char* what() {
        return "The matrix you gave has at least one invalid dimension.";
    }
};

#endif //TWITTER_DATA_TOOLS_NEURALNETWORK_H
