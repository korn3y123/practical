#include "../include/LoanApplication.h"

LoanApplication::LoanApplication(int id, int client_id, double amount, int term, LoanType loan_type,
                                 const std::string& created_at) : id(id), client_id(client_id),
                                 amount(amount), term(term), loan_type(loan_type), created_at(created_at) {
    status_history.push(status);
}

int LoanApplication::get_id() const {
    return id;
}

int LoanApplication::get_client_id() const {
    return client_id;
}

double LoanApplication::get_amount() const {
    return amount;
}

int LoanApplication::get_term() const {
    return term;
}

LoanType LoanApplication::get_loan_type() const {
    return loan_type;
}

std::string LoanApplication::get_created_at() const {
    return created_at;
}

ApplicationStatus LoanApplication::get_status() const {
    return status;
}

int LoanApplication::get_scoring_score() const {
    return scoring_score;
}

std::string LoanApplication::get_rejection_reason() const {
    return rejection_reason;
}

bool LoanApplication::validate() const {
    if (id > 0 and client_id > 0 and amount > 0 and term > 0 and !created_at.empty()) {
        return true;
    }

    return false;
}

const std::stack<ApplicationStatus>& LoanApplication::get_status_history() const {
    return status_history;
}

bool LoanApplication::set_amount(double amount) {
    if (status != ApplicationStatus::SUBMITTED or amount <= 0) {
        return false;
    }

    this->amount = amount;
    return true;
}

bool LoanApplication::set_term(int term) {
    if (status != ApplicationStatus::SUBMITTED or term <= 0) {
        return false;
    }

    this->term = term;
    return true;
}

bool LoanApplication::can_change_status(ApplicationStatus new_status) const {
    switch (status) {
        case ApplicationStatus::SUBMITTED:
            return new_status == ApplicationStatus::VERIFIED or new_status == ApplicationStatus::CANCELLED;

        case ApplicationStatus::VERIFIED:
            return new_status == ApplicationStatus::SCORED or new_status == ApplicationStatus::CANCELLED;

        case ApplicationStatus::SCORED:
            return new_status == ApplicationStatus::APPROVED or new_status == ApplicationStatus::REJECTED or
                   new_status == ApplicationStatus::CANCELLED;

        case ApplicationStatus::APPROVED:
            return new_status == ApplicationStatus::CONTRACT_PREPARED or new_status == ApplicationStatus::CANCELLED;

        case ApplicationStatus::CONTRACT_PREPARED:
            return new_status == ApplicationStatus::CONTRACT_SIGNED or new_status == ApplicationStatus::CANCELLED;

        case ApplicationStatus::CONTRACT_SIGNED:
            return new_status == ApplicationStatus::FUNDS_ISSUED or new_status == ApplicationStatus::CANCELLED;

        case ApplicationStatus::FUNDS_ISSUED:
            return new_status == ApplicationStatus::COMPLETED;

        default:
            return false;
    }
}

bool LoanApplication::change_status(ApplicationStatus new_status) {
    if (!can_change_status(new_status)) {
        return false;
    }

    status = new_status;
    status_history.push(status);

    return true;
}

bool LoanApplication::mark_verified() {
    if (!validate()) {
        return false;
    }

    return change_status(ApplicationStatus::VERIFIED);
}

bool LoanApplication::mark_scored(int score) {
    if (score < 0 or score > 100) {
        return false;
    }
    if (!change_status(ApplicationStatus::SCORED)) {
        return false;
    }

    scoring_score = score;
    return true;
}

bool LoanApplication::approve() {
    return change_status(ApplicationStatus::APPROVED);
}

bool LoanApplication::reject(const std::string& reason) {
    if (reason.empty() or !change_status(ApplicationStatus::REJECTED)) {
        return false;
    }

    rejection_reason = reason;
    return true;
}

bool LoanApplication::mark_contract_prepared() {
    return change_status(ApplicationStatus::CONTRACT_PREPARED);
}

bool LoanApplication::mark_contract_signed() {
    return change_status(ApplicationStatus::CONTRACT_SIGNED);
}

bool LoanApplication::mark_funds_issued() {
    return change_status(ApplicationStatus::FUNDS_ISSUED);
}

bool LoanApplication::complete() {
    return change_status(ApplicationStatus::COMPLETED);
}

bool LoanApplication::cancel() {
    return change_status(ApplicationStatus::CANCELLED);
}
