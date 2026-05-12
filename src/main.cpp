#include <iostream>
#include <iomanip>
#include "Loan.hpp"
#include "LoanEngine.hpp"
#include "LoanValuator.hpp"

int main() {
    Loan loan(100000.0, 0.05, 12);

    LoanEngine engine;
    auto schedule = engine.buildSchedule(loan);

    std::cout << "Amortization Schedule\n";
    std::cout << "---------------------\n";

    for (const auto& cf : schedule) {
        std::cout
        << "Month "
        << std::setw(2) << cf.month() << " | "
        << "Payment: " << std::setw(10) << cf.payment() << " | "
        << "Interest: " << std::setw(10) << cf.interest() << " | "
        << "Principal: " << std::setw(10) << cf.principal() << " | "
        << "Balance: " << std::setw(12) << cf.balance()
        << "\n";
    }

    LoanValuator valuator;

    double discountRate = 0.06; // market rate (important concept)
    double pv = valuator.presentValue(schedule, discountRate);

    std::cout << "\nLoan Present Value: " << pv << "\n";

    return 0;
}
