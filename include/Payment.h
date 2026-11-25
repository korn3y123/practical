#ifndef PAYMENT_H
#define PAYMENT_H

#include <string>
struct Payment {
    int number;
    std::string date;
    double amount;
    double principal;
    double interest;
    double remaining_debt;
};

#endif