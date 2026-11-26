#include <iostream>
#include <iomanip>
#include "../include/PaymentSchedule.h"
#include "../include/Client.h"
#include "../include/LoanApplication.h"

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

int main() {
    // test_client();
    // test_loan_application();
    test_payment_schedule();

    return 0;
}