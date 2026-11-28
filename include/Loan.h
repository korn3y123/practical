#ifndef LOAN_H
#define LOAN_H
#include <string>
#include "LoanStatus.h"
#include "PaymentSchedule.h"
#include "LoanType.h"

class Loan {
private:
    int id;
    int application_id;
    int client_id;
    double amount;
    double interest_rate;
    int term;
    double remaining_debt;
    std::string issued_at;
    LoanStatus status = LoanStatus::PENDING;
    PaymentSchedule payment_schedule;

public:
    Loan(int id, int application_id, int client_id, double amount, double interest_rate, int term);
    virtual ~Loan() = default;

    int get_id() const;
    int get_application_id() const;
    int get_client_id() const;
    double get_amount() const;
    double get_interest_rate() const;
    int get_term() const;
    double get_remaining_debt() const;
    const std::string& get_issued_at() const;
    LoanStatus get_status() const;
    const PaymentSchedule& get_payment_schedule() const;

    bool validate() const;
    double calculate_monthly_payment() const;
    double calculate_total_payment() const;
    double calculate_overpayment() const;
    bool generate_payment_schedule() ;
    bool issue(const std::string& date);

    virtual LoanType get_loan_type() const = 0;
    virtual double calculate_commission() const = 0;
};


#endif //LOAN_H
