//
// Created by rdelfin on 12/8/15.
//

#ifndef TWITTER_DATA_TOOLS_WORDNEURALNETWORK_H
#define TWITTER_DATA_TOOLS_WORDNEURALNETWORK_H

#include <Eigen/Dense>
#include <cppoptlib/meta.h>
#include <cppoptlib/solver/gradientdescentsolver.h>
#include <cppoptlib/problem.h>
#include <random>

using ActivationFunction = std::function<Eigen::MatrixXd(const Eigen::MatrixXd &)>;

class WordNeuralNetwork : public cppoptlib::Problem<double> {
public:
    WordNeuralNetwork(unsigned windowSize, unsigned embeddingSize, unsigned dictionarySize, unsigned hidden,
                      unsigned replacements, ActivationFunction func);
    Eigen::MatrixXd forward(const Eigen::MatrixXd &in);
    Eigen::MatrixXd forward();

    void setData(const Eigen::MatrixXd &phrases);

    double value(const cppoptlib::Vector<double>& x);

    void cost();
    void costDerivative();

    virtual ~WordNeuralNetwork() { }
private:
    std::default_random_engine generator;
    std::uniform_int_distribution<int> randWordDistribution;

    Eigen::MatrixXd theta1;
    Eigen::MatrixXd theta2;

    Eigen::MatrixXd embeddings;
    Eigen::VectorXd phrases;

    unsigned windowSize;
    unsigned inputN;
    unsigned hiddenN;
    unsigned outputN;

    unsigned replacements;

    ActivationFunction activation;

    void setParameters(const Eigen::VectorXd &parameters);
    Eigen::MatrixXd stochasticReplaceMiddle();
};

class DimensionsException : public std::exception {
public:
    DimensionsException() {}
    const char* what() {
        return "The matrix you gave has at least one invalid dimension.";
    }
};


#endif //TWITTER_DATA_TOOLS_WORDNEURALNETWORK_H
