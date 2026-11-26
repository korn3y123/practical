
#ifndef LOANAPPLICATION_H
#define LOANAPPLICATION_H
#include <string>
#include <stack>
#include "ApplicationStatus.h"
#include "LoanType.h"

class LoanApplication {
private:
    int id;
    int client_id;
    double amount;
    int term;
    LoanType loan_type;
    std::string created_at;
    ApplicationStatus status = ApplicationStatus::SUBMITTED;
    int scoring_score = 0;
    std::string rejection_reason;
    std::stack<ApplicationStatus> status_history;

    bool can_change_status(ApplicationStatus new_status) const;
    bool change_status(ApplicationStatus new_status);

public:
    LoanApplication(int id, int client_id, double amount, int term, LoanType loan_type, const std::string& created_at);

    int get_id() const;
    int get_client_id() const;
    double get_amount() const;
    int get_term() const;
    LoanType get_loan_type() const;
    std::string get_created_at() const;
    ApplicationStatus get_status() const;
    int get_scoring_score() const;
    std::string get_rejection_reason() const;

    const std::stack<ApplicationStatus>& get_status_history() const;

    bool set_amount(double amount);
    bool set_term(int term);

    bool validate() const;
    bool mark_verified();
    bool mark_scored(int score);
    bool approve();
    bool reject(const std::string& reason);
    bool mark_contract_prepared();
    bool mark_contract_signed();
    bool mark_funds_issued();
    bool complete();
    bool cancel();
};


#endif //LOANAPPLICATION_H
