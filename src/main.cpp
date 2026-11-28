#include <iostream>
#include <iomanip>
#include "../include/PaymentSchedule.h"
#include "../include/Client.h"
#include "../include/LoanApplication.h"
#include "../include/Loan.h"

void test_client() {
    std::cout << "===== CLIENT TEST =====" << std::endl;

    Client client(1, "Ivan Ivanov", 25, "+380991234567", 30000, 10000);

    // Test getters
    std::cout << "ID: " << client.get_id() << std::endl;
    std::cout << "Name: " << client.get_name() << std::endl;
    std::cout << "Age: " << client.get_age() << std::endl;
    std::cout << "Phone: " << client.get_phone() << std::endl;
    std::cout << "Income: " << client.get_monthly_income() << std::endl;
    std::cout << "Expenses: " << client.get_monthly_expenses() << std::endl;

    std::cout << std::boolalpha;
    std::cout << "Available income: " << client.get_available_income() << std::endl;
    std::cout << "Validate: " << client.validate() << std::endl;

    // Test setters
    client.set_name("Alex Ivanov");
    client.set_age(30);
    client.set_phone("+380501234567");
    client.set_monthly_income(40000);
    client.set_monthly_expenses(15000);

    std::cout << std::endl << "===== UPDATED CLIENT =====" << std::endl;

    std::cout << "ID: " << client.get_id() << std::endl;
    std::cout << "Name: " << client.get_name() << std::endl;
    std::cout << "Age: " << client.get_age() << std::endl;
    std::cout << "Phone: " << client.get_phone() << std::endl;
    std::cout << "Income: " << client.get_monthly_income() << std::endl;
    std::cout << "Expenses: " << client.get_monthly_expenses() << std::endl;
    std::cout << "Available income: " << client.get_available_income() << std::endl;
    std::cout << "Validate: " << client.validate() << std::endl;
}

void test_loan_application() {
    std::cout << std::endl << "===== LOAN APPLICATION TEST =====" << std::endl;
    LoanApplication application(1, 1, 50000, 12, LoanType::CONSUMER, "26.11.2026");
    std::cout << std::boolalpha;

    std::cout << "Validate: " << application.validate() << std::endl;
    std::cout << "Early approve: " << application.approve() << std::endl;
    std::cout << "Verify: " << application.mark_verified() << std::endl;
    std::cout << "Scoring: " << application.mark_scored(85) << std::endl;
    std::cout << "Approve: " << application.approve() << std::endl;
    std::cout << "Prepare contract: " << application.mark_contract_prepared() << std::endl;
    std::cout << "Sign contract: " << application.mark_contract_signed() << std::endl;
    std::cout << "Issue funds: " << application.mark_funds_issued() << std::endl;
    std::cout << "Complete: " << application.complete() << std::endl;
    std::cout << "Cancel: " << application.cancel() << std::endl;
    std::cout << "History size: " << application.get_status_history().size() << std::endl;
}

void test_payment_schedule() {
    std::cout << std::endl << "===== PAYMENT SCHEDULE TEST =====" << std::endl;
    PaymentSchedule schedule;
    std::cout << std::boolalpha;
    std::cout << "Initially generated: " << schedule.is_generated() << std::endl;

    bool result = schedule.generate(50000, 24, 12, 4727.98, "26.11.2026");

    std::cout << "Generate: " << result << std::endl;
    if (!result) {
        return;
    }

    std::cout << "Payment count: " << schedule.get_payment_count() << std::endl;
    std::cout << "Is generated: " << schedule.is_generated() << std::endl;
    std::cout << std::fixed << std::setprecision(2) << std::endl;

    for (const Payment& payment : schedule.get_payments()) {
        std::cout << payment.number << " | "
                  << payment.date << " | "
                  << payment.amount << " | "
                  << payment.principal << " | "
                  << payment.interest << " | "
                  << payment.remaining_debt << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Total payment: " << schedule.get_total_payment() << std::endl;
    std::cout << "Total interest: " << schedule.get_total_interest() << std::endl;

    const Payment& first_payment = schedule.get_payment(1);
    std::cout << "First payment: " << first_payment.amount << std::endl;

    schedule.clear();

    std::cout << "Generated after clear: " << schedule.is_generated() << std::endl;
    std::cout << "Payment count after clear: " << schedule.get_payment_count() << std::endl;
}

class TestLoan : public Loan {
public:
    using Loan::Loan;

    LoanType get_loan_type() const override {
        return LoanType::CONSUMER;
    }

    double calculate_commission() const override {
        return get_amount() * 0.02;
    }
};

void test_loan() {
    std::cout << "===== LOAN TEST =====" << std::endl;

    TestLoan loan(1, 1, 1, 50000, 24, 12);

    std::cout << std::boolalpha;
    std::cout << std::fixed << std::setprecision(2);

    // Test getters
    std::cout << "ID: " << loan.get_id() << std::endl;
    std::cout << "Application ID: " << loan.get_application_id() << std::endl;
    std::cout << "Client ID: " << loan.get_client_id() << std::endl;
    std::cout << "Amount: " << loan.get_amount() << std::endl;
    std::cout << "Interest rate: " << loan.get_interest_rate() << std::endl;
    std::cout << "Term: " << loan.get_term() << std::endl;
    std::cout << "Remaining debt: " << loan.get_remaining_debt() << std::endl;

    // Test validation
    std::cout << "Validate: " << loan.validate() << std::endl;

    // Test initial status
    std::cout << "Pending: " << (loan.get_status() == LoanStatus::PENDING) << std::endl;

    // Test calculations
    std::cout << std::endl << "===== LOAN CALCULATIONS =====" << std::endl;
    std::cout << "Monthly payment: " << loan.calculate_monthly_payment() << std::endl;
    std::cout << "Commission: " << loan.calculate_commission() << std::endl;
    std::cout << "Total payment: " << loan.calculate_total_payment() << std::endl;
    std::cout << "Overpayment: " << loan.calculate_overpayment() << std::endl;

    // Test loan issuing
    std::cout << std::endl << "===== LOAN ISSUING =====" << std::endl;
    std::cout << "Generate before issuing: " << loan.generate_payment_schedule() << std::endl;
    std::cout << "Issue without date: " << loan.issue("") << std::endl;
    std::cout << "Issue: " << loan.issue("28.11.2026") << std::endl;
    std::cout << "Active: " << (loan.get_status() == LoanStatus::ACTIVE) << std::endl;
    std::cout << "Issued at: " << loan.get_issued_at() << std::endl;
    std::cout << "Issue again: " << loan.issue("28.11.2026") << std::endl;

    // Test payment schedule
    std::cout << std::endl << "===== PAYMENT SCHEDULE =====" << std::endl;

    bool generated = loan.generate_payment_schedule();
    std::cout << "Generate: " << generated << std::endl;
    std::cout << "Generate again: " << loan.generate_payment_schedule() << std::endl;
    const PaymentSchedule& schedule = loan.get_payment_schedule();
    std::cout << "Payment count: " << schedule.get_payment_count() << std::endl;

    for (const Payment& payment : schedule.get_payments()) {
        std::cout << payment.number << " | "
                  << payment.date << " | "
                  << payment.amount << " | "
                  << payment.principal << " | "
                  << payment.interest << " | "
                  << payment.remaining_debt << std::endl;
    }

    std::cout << "Total interest: " << schedule.get_total_interest() << std::endl;
    std::cout << "Total payment with commission: " << loan.calculate_total_payment() << std::endl;
    std::cout << "Overpayment: " << loan.calculate_overpayment() << std::endl;
    std::cout << "Actual remaining debt: " << loan.get_remaining_debt() << std::endl;

    // Test invalid loan
    std::cout << std::endl << "===== INVALID LOAN TEST =====" << std::endl;
    TestLoan invalid_loan(2, 2, 1, -50000, 24, 12);
    std::cout << "Validate: " << invalid_loan.validate() << std::endl;
    std::cout << "Issue: " << invalid_loan.issue("28.11.2026") << std::endl;

    // Test zero interest rate
    std::cout << std::endl << "===== ZERO INTEREST TEST =====" << std::endl;
    TestLoan zero_interest_loan(3, 3, 1, 12000, 0, 12);
    std::cout << "Validate: " << zero_interest_loan.validate() << std::endl;
    std::cout << "Monthly payment: " << zero_interest_loan.calculate_monthly_payment() << std::endl;
}

int main() {
    // test_client();
    // test_loan_application();
    // test_payment_schedule();
    test_loan();

    return 0;
}