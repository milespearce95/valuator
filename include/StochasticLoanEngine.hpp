#pragma once

#include <vector>
#include <cmath>
#include "Loan.hpp"
#include "Cashflow.hpp"
#include "LoanStochasticModel.hpp"
#include "LoanStates.hpp"

struct SimulationResult {
    std::vector<Cashflow> cashflows;
    LoanState finalState;
};

class StochasticLoanEngine {
public:
    SimulationResult simulate(const Loan& loan,
                              LoanStochasticModel& model) {

        std::vector<Cashflow> path;

        double balance = loan.principal();
        double r = loan.annualRate() / 12.0;

        double payment = (r * loan.principal()) /
                         (1.0 - std::pow(1.0 + r, -loan.termMonths()));

        for (int t = 1; t <= loan.termMonths(); t++) {

            // loan already finished
            if (balance <= 0.0) {
                return {path, LoanState::Prepaid};
            }

            // 1. default event (absorbing state)
            if (model.defaultEvent()) {

                // assume zero recovery for now
                path.emplace_back(t, 0.0, 0.0, 0.0, 0.0);
                return {path, LoanState::Defaulted};
            }

            // 2. prepayment event (full redemption)
            if (model.prepayEvent()) {

                path.emplace_back(t, balance, 0.0, balance, 0.0);
                return {path, LoanState::Prepaid};
            }

            // 3. normal amortization step
            double interest = balance * r;
            double principal = payment - interest;

            balance -= principal;

            path.emplace_back(t, payment, interest, principal, balance);
        }

        return {path, LoanState::Active};
    }
};
