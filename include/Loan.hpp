#pragma once

class Loan {
private:
    double principal_;
    double annualRate_;
    int termMonths_;

public:
    Loan(double principal, double annualRate, int termMonths)
        : principal_(principal),
          annualRate_(annualRate),
          termMonths_(termMonths) {}

    double principal() const { return principal_; }
    double annualRate() const { return annualRate_; }
    int termMonths() const { return termMonths_; }
};
