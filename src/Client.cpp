#include "../include/Client.h"

Client::Client(int id, const std::string& name, int age, const std::string& phone, double monthly_income,
               double monthly_expenses) : id(id), name(name), age(age), phone(phone),
               monthly_income(monthly_income), monthly_expenses(monthly_expenses) {}

void Client::set_name(const std::string& name) {
    this->name = name;
}

void Client::set_age(int age) {
    this->age = age;
}

void Client::set_phone(const std::string& phone) {
    this->phone = phone;
}

void Client::set_monthly_income(double monthly_income) {
    this->monthly_income = monthly_income;
}

void Client::set_monthly_expenses(double monthly_expenses) {
    this->monthly_expenses = monthly_expenses;
}

int Client::get_id() const {
    return id;
}

std::string Client::get_name() const {
    return name;
}

int Client::get_age() const {
    return age;
}

std::string Client::get_phone() const {
    return phone;
}

double Client::get_monthly_income() const {
    return monthly_income;
}

double Client::get_monthly_expenses() const {
    return monthly_expenses;
}

double Client::get_available_income() const {
    return monthly_income - monthly_expenses;
}

bool Client::validate() const {
    return id > 0 and !name.empty() and age >= 18 and !phone.empty() and monthly_income >= 0
           and monthly_expenses >= 0;
}
