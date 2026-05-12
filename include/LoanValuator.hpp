#pragma once

#include <vector>
#include <cmath>
#include "Cashflow.hpp"

class LoanValuator {
private:
    static double monthlyRate(double annualRate) {
        return annualRate / 12.0;
    }

public:
    // Discount cashflows to present value
    double presentValue(const std::vector<Cashflow>& cashflows,
                        double annualDiscountRate) {

        double r = monthlyRate(annualDiscountRate);
        double pv = 0.0;

        for (const auto& cf : cashflows) {
            int t = cf.month();

            double discounted = cf.payment() / std::pow(1.0 + r, t);
            pv += discounted;
        }

        return pv;
    }
};
