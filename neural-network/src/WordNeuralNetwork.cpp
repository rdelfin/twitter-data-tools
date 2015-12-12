//
// Created by rdelfin on 12/8/15.
//

#include "neural-network/WordNeuralNetwork.h"
#include <algorithm>

double zeroMax(double in) {
    return std::max(0.0, in);
}

WordNeuralNetwork::WordNeuralNetwork(unsigned windowSize, unsigned embeddingSize, unsigned dictionarySize,
                                     unsigned replacements, unsigned hidden, ActivationFunction func)
        : activation(func), inputN(windowSize*embeddingSize), outputN(1), hiddenN(hidden), windowSize(windowSize),
          replacements(replacements), embeddings(embeddingSize, dictionarySize + 1),
          theta1(Eigen::MatrixXd::Random(windowSize*embeddingSize + 1, hidden)),
          theta2(Eigen::MatrixXd::Random(hidden + 1, 1)), randWordDistribution(0, dictionarySize - 1) {

}

void WordNeuralNetwork::setData(const Eigen::MatrixXd &phrases) {
    if(phrases.cols() != windowSize) {
        throw DimensionsException();
    }

    this->phrases = phrases;
}

Eigen::MatrixXd WordNeuralNetwork::forward() {
    return forward(phrases);
}

Eigen::MatrixXd WordNeuralNetwork::forward(const Eigen::MatrixXd &in) {
    Eigen::MatrixXd embeddedInput(in.rows(), inputN);

    /* Iterates over every word and creates a new vector where the word indexes are replaced with their vector
     * embedding representations. */
    for(int phrase = 0; phrase < in.rows(); phrase++) {
        for(int word = 0; word < in.cols(); word++) {
            for(int v = 0; v < embeddings.rows(); v++) {
                embeddedInput(phrase, word*embeddings.rows() + v) = embeddings(v, (int)in(phrase, word));
            }
        }
    }

    Eigen::MatrixXd a1;
    a1.resize(embeddedInput.rows(), embeddedInput.cols() + 1);
    a1 << Eigen::MatrixXd::Constant(embeddedInput.rows(), 1, 1), embeddedInput;

    Eigen::MatrixXd s2 = a1 * theta1;
    Eigen::MatrixXd tempA2 = activation(s2);


    Eigen::MatrixXd a2;
    a2.resize(tempA2.rows(), tempA2.cols() + 1);
    a2 << Eigen::MatrixXd::Constant(tempA2.rows(), 1, 1), tempA2;
    Eigen::MatrixXd s3 = a2 * theta2;

    return s3;
}

double WordNeuralNetwork::value(const cppoptlib::Vector<double> &x) {
    setParameters(x);

    Eigen::VectorXd result = forward();                   /* Sample size x 1 */
    Eigen::MatrixXd replaced = stochasticReplaceMiddle(); /* Sample size x (windowSize * replacements) */
    Eigen::MatrixXd replacedResult(replaced.rows(), replacements);

    for (int i = 0; i < replacements; i++) {
        Eigen::MatrixXd column = replaced.block(0, i * windowSize, replaced.rows() - 1, (i+1) * windowSize - 1);
        column = forward(column);
        replacedResult.block(0, i * windowSize, replaced.rows() - 1, (i+1) * windowSize - 1) = column;
    }

    Eigen::MatrixXd replicatedResult(replaced.rows(), replaced.cols());

    for(int i = 0; i < replicatedResult.rows(); i++) {
        for(int j = 0; j < replicatedResult.cols(); j++) {
            replicatedResult(i, j) = result[i];
        }
    }

    // These three lines implement the max function described in line 4 of the paper (Collobert, Weston, 2008)
    Eigen::MatrixXd scores = Eigen::MatrixXd::Constant(replaced.rows(), replaced.cols(), 1) - replicatedResult + replacedResult;
    scores = scores.unaryExpr(std::ptr_fun(zeroMax));
    return scores.sum();
}

void WordNeuralNetwork::setParameters(const Eigen::VectorXd &parameters) {
    long parametersIndex = 0;

    /* Embeddings */
    for(int i = 0; i < embeddings.rows(); i++) {
        for(int j = 0; j < embeddings.cols(); j++) {
            embeddings(i, j) = parameters[parametersIndex];
            parametersIndex++;
        }
    }

    /* Theta 1 */
    for(int i = 0; i < theta1.rows(); i++) {
        for(int j = 0; j < theta1.cols(); j++) {
            theta1(i, j) = parameters[parametersIndex];
            parametersIndex++;
        }
    }

    /* Theta 2 */
    for(int i = 0; i < theta2.rows(); i++) {
        for(int j = 0; j < theta2.cols(); j++) {
            theta2(i, j) = parameters[parametersIndex];
            parametersIndex++;
        }
    }
}

Eigen::MatrixXd WordNeuralNetwork::stochasticReplaceMiddle() {
    Eigen::MatrixXd data = phrases;

    for(int i = 0; i < data.rows(); i++) {
        data(i, (int)ceil((float)windowSize / 2.0)) = randWordDistribution(generator);
    }

    return data;
}