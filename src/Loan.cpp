#include "../include/Loan.h"

Loan::Loan(int id, int application_id, int client_id,
           double amount, double interest_rate, int term) : id(id), application_id(application_id), client_id(client_id),
           amount(amount), interest_rate(interest_rate), term(term), remaining_debt(amount) {}

int Loan::get_id() const {
    return id;
}

int Loan::get_application_id() const {
    return application_id;
}

int Loan::get_client_id() const {
    return client_id;
}

double Loan::get_amount() const {
    return amount;
}

double Loan::get_interest_rate() const {
    return interest_rate;
}

int Loan::get_term() const {
    return term;
}

double Loan::get_remaining_debt() const {
    return remaining_debt;
}

const std::string& Loan::get_issued_at() const {
    return issued_at;
}

LoanStatus Loan::get_status() const {
    return status;
}

const PaymentSchedule& Loan::get_payment_schedule() const {
    return payment_schedule;
}

bool Loan::validate() const {
    return id > 0 and application_id > 0 and client_id > 0 and std::isfinite(amount) and
           std::isfinite(interest_rate) and amount > 0 and interest_rate >= 0 and term > 0;
}

double Loan::calculate_monthly_payment() const {
    if (!validate()) {
        return 0;
    }

    double monthly_rate = interest_rate / 1200.0;

    if (monthly_rate == 0) {
        return std::round(amount / term * 100) / 100;
    }

    double monthly_payment = amount * monthly_rate / (1 - std::pow(1 + monthly_rate, -term));

    return std::round(monthly_payment * 100) / 100;
}

double Loan::calculate_total_payment() const {
    if (!validate()) {
        return 0;
    }

    double total_payment;

    if (payment_schedule.is_generated()) {
        total_payment = payment_schedule.get_total_payment();
    } else {
        total_payment = calculate_monthly_payment() * term;
    }

    total_payment += calculate_commission();

    return std::round(total_payment * 100) / 100;
}

double Loan::calculate_overpayment() const {
    if (!validate()) {
        return 0;
    }

    return std::round((calculate_total_payment() - amount) * 100) / 100;
}

bool Loan::issue(const std::string& date) {
    if (!validate() or status != LoanStatus::PENDING or date.empty()) {
        return false;
    }
    issued_at = date;
    status = LoanStatus::ACTIVE;

    return true;
}

bool Loan::generate_payment_schedule() {
    if (status != LoanStatus::ACTIVE or payment_schedule.is_generated()) {
        return false;
    }

    return payment_schedule.generate(amount, interest_rate, term, calculate_monthly_payment(), issued_at);
}