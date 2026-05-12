#pragma once

#include <vector>
#include <cmath>
#include "Loan.hpp"
#include "Cashflow.hpp"

class LoanEngine {
private:
    static double monthlyRate(double annualRate) {
        return annualRate / 12.0;
    }

    static double monthlyPayment(double P, double r, int n) {
        return (r * P) / (1.0 - std::pow(1.0 + r, -n));
    }

public:
    std::vector<Cashflow> buildSchedule(const Loan& loan) {
        std::vector<Cashflow> schedule;

        double balance = loan.principal();
        double r = monthlyRate(loan.annualRate());
        double payment = monthlyPayment(balance, r, loan.termMonths());

        for (int i = 1; i <= loan.termMonths(); i++) {

            double interest = balance * r;
            double principal = payment - interest;
            balance -= principal;

            schedule.emplace_back(
                i,
                payment,
                interest,
                principal,
                balance
            );
        }

        return schedule;
    }
};
