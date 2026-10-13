#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <iostream>

class Customer {
private:
    std::string customerId;
    std::string name;
    std::string phone;

public:
    Customer();
    Customer(const std::string& id, const std::string& name, const std::string& phone);
    ~Customer();

    std::string getId() const;
    std::string getName() const;
    std::string getPhone() const;

    void setName(const std::string& newName);
    void setPhone(const std::string& newPhone);

    void display() const;
};

#endif