#pragma once

#include <vector>
#include "StochasticLoanEngine.hpp"
#include "LoanStates.hpp"

class PortfolioMonteCarlo {
public:
    struct SurvivalPoint {
        int month;
        double survivalRate;
    };

    struct DefaultPoint {
        int month;
        double defaultRate;
    };

    struct Result {
        std::vector<SurvivalPoint> survivalCurve;
        std::vector<DefaultPoint> defaultCurve;
    };

    Result run(const Loan& loan,
               LoanStochasticModel& model,
               int simulations,
               int horizonMonths) {

        StochasticLoanEngine engine;

        std::vector<int> aliveCount(horizonMonths, 0);
        std::vector<int> defaultCount(horizonMonths, 0);

        for (int i = 0; i < simulations; i++) {

            auto sim = engine.simulate(loan, model);

            int lastMonth = (int)sim.cashflows.size();

            LoanState state = sim.finalState;

            // track survival
            for (int t = 0; t < lastMonth && t < horizonMonths; t++) {
                aliveCount[t]++;
            }

            // track defaults (only if defaulted)
            if (state == LoanState::Defaulted) {
                for (int t = lastMonth - 1; t < horizonMonths; t++) {
                    if (t >= 0) defaultCount[t]++;
                }
            }
        }

        Result result;

        for (int t = 0; t < horizonMonths; t++) {

            double survival = (double)aliveCount[t] / simulations;
            double defaultRate = (double)defaultCount[t] / simulations;

            result.survivalCurve.push_back({t + 1, survival});
            result.defaultCurve.push_back({t + 1, defaultRate});
        }

        return result;
    }
};
