#pragma once

#include <vector>
#include <cmath>
#include <limits>
#include "Cashflow.hpp"

class CashflowAnalytics {
private:
    static double npv(const std::vector<Cashflow>& cf, double rate) {
        double pv = 0.0;

        for (const auto& c : cf) {
            int t = c.month();
            double cash = c.payment();

            pv += cash / std::pow(1.0 + rate, t);
        }

        return pv;
    }

    static double d_npv(const std::vector<Cashflow>& cf, double rate) {
        double d = 0.0;

        for (const auto& c : cf) {
            int t = c.month();
            double cash = c.payment();

            d += -t * cash / std::pow(1.0 + rate, t + 1.0);
        }

        return d;
    }

public:
    // Present Value
    double presentValue(const std::vector<Cashflow>& cf, double rate) {
        return npv(cf, rate);
    }

    // IRR (Newton-Raphson)
    double irr(const std::vector<Cashflow>& cf) {
        double guess = 0.05;

        for (int i = 0; i < 50; i++) {

            double f = npv(cf, guess);
            double df = d_npv(cf, guess);

            if (std::fabs(df) < 1e-10)
                break;

            double next = guess - f / df;

            if (std::fabs(next - guess) < 1e-8)
                return next;

            guess = next;
        }

        return guess;
    }
};
