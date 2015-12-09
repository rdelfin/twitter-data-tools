//
// Created by rdelfin on 12/7/15.
//


#include <neural-network/WordNeuralNetwork.h>

#include <Eigen/Dense>
#include <functional>
#include <cmath>

double recp(double x) {
    return 1.0 / x;
}

int main(int argc, char* argv[]) {
    WordNeuralNetwork network(5, 3, 1, [](const Eigen::MatrixXd& in)-> Eigen::MatrixXd {
        Eigen::MatrixXd exponent = (-1.0 * in).unaryExpr(std::ptr_fun(exp));
        Eigen::MatrixXd ones = Eigen::MatrixXd::Constant(in.rows(), in.cols(), 1.0);
        return (ones + exponent).unaryExpr(std::ptr_fun(recp));
    });


    Eigen::MatrixXd in = Eigen::MatrixXd::Random(4, 5);
    Eigen::MatrixXd out = network(in);
    std::cout << "in = " << std::endl
              << in << std::endl
              << "out = " << std::endl
              << out << std::endl;

    return 0;
}