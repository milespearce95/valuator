#pragma once

#include <random>

class LoanStochasticModel {
private:
    double monthlyPrepayProb_;
    double monthlyDefaultProb_;

    std::mt19937 gen_;
    std::uniform_real_distribution<double> dist_;

public:
    LoanStochasticModel(double prepayProb, double defaultProb)
        : monthlyPrepayProb_(prepayProb),
          monthlyDefaultProb_(defaultProb),
          gen_(std::random_device{}()),
          dist_(0.0, 1.0) {}

    bool prepayEvent() {
        return dist_(gen_) < monthlyPrepayProb_;
    }

    bool defaultEvent() {
        return dist_(gen_) < monthlyDefaultProb_;
    }
};
