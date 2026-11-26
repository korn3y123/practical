#include <iostream>
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

    LoanApplication application(1, 1, 50000, 12,
                                LoanType::CONSUMER, "26.11.2026");

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

int main() {
    test_client();
    test_loan_application();

    return 0;
}