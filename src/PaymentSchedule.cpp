#include "../include/PaymentSchedule.h"

#include <cmath>
#include <chrono>
#include <sstream>
#include <iomanip>
#include <stdexcept>

const std::vector<Payment>& PaymentSchedule::get_payments() const {
    return payments;
}

const Payment& PaymentSchedule::get_payment(int number) const {
    if (number <= 0) {
        throw std::out_of_range("Invalid payment number");
    }

    return payments.at(number - 1);
}

int PaymentSchedule::get_payment_count() const {
    return static_cast<int>(payments.size());
}

double PaymentSchedule::get_total_payment() const {
    return total_payment;
}

double PaymentSchedule::get_total_interest() const {
    return total_interest;
}

bool PaymentSchedule::is_generated() const {
    return !payments.empty();
}

void PaymentSchedule::clear() {
    payments.clear();

    total_payment = 0;
    total_interest = 0;
}

double PaymentSchedule::calculate_interest(double remaining_debt, double monthly_rate) const {
    return std::round(remaining_debt * monthly_rate * 100) / 100;
}

double PaymentSchedule::calculate_principal(double monthly_payment, double interest) const {
    return std::round((monthly_payment - interest) * 100) / 100;
}

std::string PaymentSchedule::calculate_payment_date(const std::string& issued_at, int number) const {
    int day, month, year;
    char separator1, separator2;

    std::istringstream stream(issued_at);

    if (!(stream >> day >> separator1 >> month >> separator2 >> year) or separator1 != '.' or separator2 != '.' or
        day < 1 or day > 31 or month < 1 or month > 12 or year < 1 or year > 9999) {
        return "";
    }

    stream >> std::ws;

    if (!stream.eof()) {
        return "";
    }

    std::chrono::year_month_day date{std::chrono::year(year), std::chrono::month(month),std::chrono::day(day)};

    if (!date.ok()) {
        return "";
    }
    date += std::chrono::months(number);

    if (!date.ok()) {
        date = std::chrono::year_month_day{date.year() / date.month() / std::chrono::last};
    }

    std::ostringstream result;

    result << std::setfill('0') << std::setw(2) << static_cast<unsigned>(date.day())
           << "." << std::setw(2) << static_cast<unsigned>(date.month())
           << "." << std::setw(4) << static_cast<int>(date.year());

    return result.str();
}

bool PaymentSchedule::generate(double amount, double interest_rate, int term, double monthly_payment,
                               const std::string& issued_at) {
    if (amount <= 0 or interest_rate < 0 or term <= 0 or monthly_payment <= 0) {
        return false;
    }
    if (calculate_payment_date(issued_at, 0).empty()) {
        return false;
    }

    double monthly_rate = interest_rate / 1200.0;
    if (monthly_payment <= amount * monthly_rate) {
        return false;
    }
    double expected_payment;

    if (monthly_rate == 0) {
        expected_payment = amount / term;
    } else {
        expected_payment = amount * monthly_rate / (1 - std::pow(1 + monthly_rate, -term));
    }

    expected_payment = std::round(expected_payment * 100) / 100;
    if (std::abs(monthly_payment - expected_payment) > 0.01) {
        return false;
    }

    clear();

    double remaining_debt = std::round(amount * 100) / 100;

    payments.reserve(term);

    for (int i = 1; i <= term; i++) {
        double interest = calculate_interest(remaining_debt, monthly_rate);
        double principal = calculate_principal(monthly_payment, interest);

        if (i == term or principal > remaining_debt) {
            principal = remaining_debt;
        }

        remaining_debt -= principal;
        remaining_debt = std::round(remaining_debt * 100) / 100;
        double payment_amount = principal + interest;

        Payment payment{i, calculate_payment_date(issued_at, i), payment_amount, principal, interest, remaining_debt};
        payments.push_back(payment);

        total_payment += payment_amount;
        total_interest += interest;
    }

    total_payment = std::round(total_payment * 100) / 100;
    total_interest = std::round(total_interest * 100) / 100;

    return true;
}