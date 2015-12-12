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
#include <tools-lib/csv.h>
#include <tools-lib/StringUtils.h>

long getDictionarySize();
Eigen::MatrixXd getAllWindows(int windowSize, long dictionarySize);

double recp(double x) {
    return 1.0 / x;
}

int main(int argc, char* argv[]) {

    int windowSize = 5;

    std::cerr << "Dictionary size being obtained..." << std::endl;

    long dictionarySize = getDictionarySize();

    std::cerr << "Dictionary size obtained!" << std::endl << "Obtaining windows..." << std::endl;

    Eigen::MatrixXd data = getAllWindows(windowSize, dictionarySize);

    std::cerr << "Windows created!" << std::endl;


    /*                        windowSize, embeddingSize, dictionarySize, hidden, replacements */
    WordNeuralNetwork network(5,          10,            10000,          10,     10000,
    [](const Eigen::MatrixXd& in)-> Eigen::MatrixXd {
        Eigen::MatrixXd exponent = (-1.0 * in).unaryExpr(std::ptr_fun(exp));
        Eigen::MatrixXd ones = Eigen::MatrixXd::Constant(in.rows(), in.cols(), 1.0);
        return (ones + exponent).unaryExpr(std::ptr_fun(recp));
    });

    std::cerr << "Setting data..." << std::endl;

    network.setData(data);

    Eigen::MatrixXd result = network.forward();
    std::cout << "Result in R^" << result.rows() << "x" << result.cols() << std::endl;

    /*cppoptlib::LbfgsSolver<double> solver;
    cppoptlib::Vector<double> startParams = cppoptlib::Vector<double>::Random(network.numParams());
    solver.minimize(network, startParams);*/

    return 0;
}

long getDictionarySize()
{
    long result = 0;
    io::LineReader dictonaryIn("data/dictionary.txt");

    char* line;

    while( (line = dictonaryIn.next_line()) != nullptr) {
        result++;
    }

    return result;
}

Eigen::MatrixXd getAllWindows(int windowSize, long dictionarySize)
{
    Eigen::MatrixXd result(1, windowSize);
    io::LineReader tweetsIn("data/tweets.txt");

    char* line;
    while( (line = tweetsIn.next_line()) != nullptr) {
        std::vector<std::string> items = tl::StringUtils::split(std::string(line), ',');

        for(int word = 0; word < items.size(); word++) {
            Eigen::VectorXd windowVector(windowSize);
            for(int windowIdx = 0; windowIdx < windowSize; windowIdx++) {
                int sentenceIdx = word - windowIdx + (windowSize / 2);
                windowVector[windowIdx] = sentenceIdx < 0 || sentenceIdx >= items.size()
                                          ? dictionarySize
                                          : atoi(items[sentenceIdx].c_str());
            }

            result.conservativeResize(result.rows() + 1, windowSize);
            result.row(result.rows() - 1) = windowVector;
        }
    }

    return result;

}