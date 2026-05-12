#pragma once

class Cashflow {
private:
    int month_;
    double payment_;
    double interest_;
    double principal_;
    double balance_;

public:
    Cashflow(int month,
             double payment,
             double interest,
             double principal,
             double balance)
        : month_(month),
          payment_(payment),
          interest_(interest),
          principal_(principal),
          balance_(balance) {}

    int month() const { return month_; }
    double payment() const { return payment_; }
    double interest() const { return interest_; }
    double principal() const { return principal_; }
    double balance() const { return balance_; }
};
