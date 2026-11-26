#ifndef PAYMENTSCHEDULE_H
#define PAYMENTSCHEDULE_H

#include <vector>
#include <string>
#include "Payment.h"

class PaymentSchedule {
private:
    std::vector<Payment> payments;

    double total_payment = 0;
    double total_interest = 0;

    double calculate_interest(double remaining_debt, double monthly_rate) const;
    double calculate_principal(double monthly_payment, double interest) const;
    std::string calculate_payment_date(const std::string& issued_at, int number) const;

public:
    PaymentSchedule() = default;
    bool generate(double amount, double interest_rate, int term, double monthly_payment, const std::string& issued_at);

    const std::vector<Payment>& get_payments() const;
    const Payment& get_payment(int number) const;
    int get_payment_count() const;
    double get_total_payment() const;
    double get_total_interest() const;
    bool is_generated() const;

    void clear();
};

#endif // PAYMENTSCHEDULE_H