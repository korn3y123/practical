#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
private:
    int id;
    std::string name;
    int age;
    std::string phone;
    double monthly_income;
    double monthly_expenses;

public:
    Client(int id, const std::string& name, int age, const std::string& phone, double monthly_income,
        double monthly_expenses);
    int get_id() const;
    std::string get_name() const;
    int get_age() const;
    std::string get_phone() const;
    double get_monthly_income() const;
    double get_monthly_expenses() const;

    void set_name(const std::string& name);
    void set_age(int age);
    void set_phone(const std::string& phone);
    void set_monthly_income(double income);
    void set_monthly_expenses(double expenses);

    double get_available_income() const;
    bool validate() const;
};

#endif //CLIENT_H
