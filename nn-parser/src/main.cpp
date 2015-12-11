//
// Created by rdelfin on 12/7/15.
//


#include <neural-network/WordNeuralNetwork.h>

#include <Eigen/Dense>
#include <functional>
#include <cmath>
#include <cppoptlib/meta.h>
#include <cppoptlib/problem.h>
#include <cppoptlib/solver/lbfgssolver.h>

double recp(double x) {
    return 1.0 / x;
}

int main(int argc, char* argv[]) {
    /*                        windowSize, embeddingSize, dictionarySize, hidden, replacements */
    WordNeuralNetwork network(5,          10,            10000,          10,     10000,
    [](const Eigen::MatrixXd& in)-> Eigen::MatrixXd {
        Eigen::MatrixXd exponent = (-1.0 * in).unaryExpr(std::ptr_fun(exp));
        Eigen::MatrixXd ones = Eigen::MatrixXd::Constant(in.rows(), in.cols(), 1.0);
        return (ones + exponent).unaryExpr(std::ptr_fun(recp));
    });

    cppoptlib::LbfgsSolver<double> solver;
    cppoptlib::Vector<double> startParams(10);
    solver.minimize(network, startParams);

    return 0;
}