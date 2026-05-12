#include <iostream>
#include "Loan.hpp"
#include "LoanStochasticModel.hpp"
#include "PortfolioMonteCarlo.hpp"

int main() {

    // 1. Define a loan contract
    Loan loan(
        100000.0,  // principal
        0.05,      // annual interest rate
        24         // term in months
    );

    // 2. Define stochastic behaviour
    LoanStochasticModel model(
        0.01,  // 1% monthly prepayment probability
        0.005  // 0.5% monthly default probability
    );

    // 3. Run Monte Carlo simulation
    PortfolioMonteCarlo mc;

    int simulations = 10000;
    int horizon = 24;

    auto result = mc.run(loan, model, simulations, horizon);

    // 4. Output survival curve
    std::cout << "Month | Survival | Default\n";
    std::cout << "--------------------------\n";

    for (int i = 0; i < horizon; i++) {

        std::cout
            << (i + 1) << "     | "
            << result.survivalCurve[i].survivalRate << "   | "
            << result.defaultCurve[i].defaultRate << "\n";
    }

    return 0;
}
