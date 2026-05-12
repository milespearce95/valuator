#pragma once

#include <vector>
#include "StochasticLoanEngine.hpp"

class PortfolioSimulator {
public:
    struct SurvivalPoint {
        int month;
        double survivalRate;
    };

    std::vector<SurvivalPoint> simulateSurvival(
        const Loan& loan,
        LoanStochasticModel& model,
        int simulations,
        int horizonMonths) {

        std::vector<int> aliveCount(horizonMonths, 0);

        StochasticLoanEngine engine;

        for (int i = 0; i < simulations; i++) {

            auto result = engine.simulate(loan, model);

            int lastAlive = (int)result.cashflows.size();

            for (int t = 0; t < lastAlive && t < horizonMonths; t++) {
                aliveCount[t]++;
            }
        }

        std::vector<SurvivalPoint> curve;

        for (int t = 0; t < horizonMonths; t++) {
            curve.push_back({
                t + 1,
                (double)aliveCount[t] / simulations
            });
        }

        return curve;
    }
};
