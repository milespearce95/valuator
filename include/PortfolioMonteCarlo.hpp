#pragma once

#include <vector>
#include "StochasticLoanEngine.hpp"
#include "CashflowAnalytics.hpp"
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

        // NEW: financial outputs
        std::vector<double> irrDistribution;
        std::vector<double> pvDistribution;
    };

    Result run(const Loan& loan,
               LoanStochasticModel& model,
               int simulations,
               int horizonMonths,
               double discountRate = 0.05) {

        StochasticLoanEngine engine;
        CashflowAnalytics analytics;

        std::vector<int> alive(horizonMonths, 0);
        std::vector<int> defaulted(horizonMonths, 0);

        Result result;

        for (int i = 0; i < simulations; i++) {

            auto sim = engine.simulate(loan, model);

            // -----------------------------
            // 1. survival + default stats
            // -----------------------------
            int last = (int)sim.cashflows.size();

            for (int t = 0; t < last && t < horizonMonths; t++) {
                alive[t]++;
            }

            if (sim.finalState == LoanState::Defaulted) {
                for (int t = last - 1; t < horizonMonths; t++) {
                    if (t >= 0) defaulted[t]++;
                }
            }

            // -----------------------------
            // 2. financial metrics per path
            // -----------------------------
            double irr = analytics.irr(sim.cashflows);
            double pv  = analytics.presentValue(sim.cashflows, discountRate);

            result.irrDistribution.push_back(irr);
            result.pvDistribution.push_back(pv);
        }

        // -----------------------------
        // 3. build curves
        // -----------------------------
        for (int t = 0; t < horizonMonths; t++) {

            result.survivalCurve.push_back({
                t + 1,
                (double)alive[t] / simulations
            });

            result.defaultCurve.push_back({
                t + 1,
                (double)defaulted[t] / simulations
            });
        }

        return result;
    }
};
