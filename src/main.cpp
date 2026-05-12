#include <iostream>
#include "Loan.hpp"
#include "Valuator.hpp"

int main() {
    Loan loan(100000.0, 0.05, 12);

    Valuator valuator;
    auto schedule = valuator.buildSchedule(loan);

    std::cout << "Loan Amortization Schedule\n";
    std::cout << "--------------------------\n";

    for (const auto& cf : schedule) {
        std::cout
            << "Month " << cf.month()
            << " | Payment: " << cf.payment()
            << " | Interest: " << cf.interest()
            << " | Principal: " << cf.principal()
            << " | Balance: " << cf.balance()
            << "\n";
    }

    return 0;
}
