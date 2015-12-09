//
// Created by rdelfin on 12/8/15.
//

#ifndef TWITTER_DATA_TOOLS_WORDNEURALNETWORK_H
#define TWITTER_DATA_TOOLS_WORDNEURALNETWORK_H

#include <Eigen/Dense>
#include <cppoptlib/meta.h>
#include <cppoptlib/solver/gradientdescentsolver.h>
#include <cppoptlib/problem.h>

using ActivationFunction = std::function<Eigen::MatrixXd(const Eigen::MatrixXd &)>;

class WordNeuralNetwork : public cppoptlib::Problem<double> {
public:
    WordNeuralNetwork(unsigned inputs, unsigned outputs, unsigned hidden, ActivationFunction func);
    Eigen::MatrixXd operator()(const Eigen::MatrixXd& in);

    void setX(const Eigen::MatrixXd &x);

    double value(const cppoptlib::Vector<double>& x);

    void cost();
    void costDerivative();

    virtual ~WordNeuralNetwork() { }
private:
    Eigen::MatrixXd theta1;
    Eigen::MatrixXd theta2;

    Eigen::MatrixXd x;

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
