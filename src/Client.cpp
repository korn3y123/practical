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