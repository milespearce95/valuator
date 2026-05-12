#include <iostream>

#include "Loan.hpp"
#include "LoanStochasticModel.hpp"
#include "PortfolioMonteCarlo.hpp"
#include "PortfolioAnalytics.hpp"
#include "CurveExporter.hpp"

int main() {

    Loan loan(100000, 0.05, 24);

    LoanStochasticModel model(
        0.01,   // prepay
        0.005   // default
    );

    PortfolioMonteCarlo mc;
    PortfolioAnalytics analytics;

    int sims = 10000;
    int horizon = 24;

    auto result = mc.run(loan, model, sims, horizon);

    
    std::cout << "Survival / Default curves built\n";
    CurveExporter exporter;
    exporter.exportSurvival(result.survivalCurve, "survival.csv");
    exporter.exportDefault(result.defaultCurve, "default.csv");
    
    auto summary = analytics.analyze(
        result.irrDistribution,
        result.pvDistribution
    );


    std::cout << "\n=== Portfolio Analytics ===\n";

    std::cout << "Mean IRR: " << summary.meanIRR << "\n";
    std::cout << "IRR StdDev: " << summary.irrStdDev << "\n";

    std::cout << "IRR P5:  " << summary.irrP5 << "\n";
    std::cout << "IRR P50: " << summary.irrP50 << "\n";
    std::cout << "IRR P95: " << summary.irrP95 << "\n";

    std::cout << "Mean PV: " << summary.meanPV << "\n";

    return 0;
}
