
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
    ApplicationStatus status;
    int scoring_score;
    std::string rejection_reason;
    std::stack<ApplicationStatus> status_history;

public:

};


#endif //LOANAPPLICATION_H
