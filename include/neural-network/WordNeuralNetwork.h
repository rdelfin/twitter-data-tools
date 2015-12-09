//
// Created by rdelfin on 12/8/15.
//

#ifndef TWITTER_DATA_TOOLS_WORDNEURALNETWORK_H
#define TWITTER_DATA_TOOLS_WORDNEURALNETWORK_H

#include <armadillo>
#include <cppoptlib/meta.h>
#include <cppoptlib/solver/gradientdescentsolver.h>
#include <cppoptlib/problem.h>

using ActivationFunction = std::function<arma::mat(const arma::mat &)>;

class WordNeuralNetwork : public cppoptlib::Problem<double> {
public:
    WordNeuralNetwork(unsigned inputs, unsigned outputs, unsigned hidden, ActivationFunction func);
    arma::mat operator()(const arma::mat& in);

    void setX(const arma::mat &x);

    double value(const cppoptlib::Vector<double>& x);

    void cost();
    void costDerivative();

    virtual ~WordNeuralNetwork() { }
private:
    arma::mat theta1;
    arma::mat theta2;

    arma::mat x;

    unsigned inputN;
    unsigned hiddenN;
    unsigned outputN;

    ActivationFunction activation;
};

class DimensionsException : public std::exception {
public:
    DimensionsException() {}
    const char* what() {
        return "The matrix you gave has at least one invalid dimension.";
    }
};


#endif //TWITTER_DATA_TOOLS_WORDNEURALNETWORK_H
