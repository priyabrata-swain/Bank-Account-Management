#include "Customer.h"
#include <iomanip>

Customer::Customer() : customerId(""), name(""), phone("") {}

Customer::Customer(const std::string& id, const std::string& name, const std::string& phone)
    : customerId(id), name(name), phone(phone) {}

Customer::~Customer() {}

std::string Customer::getId() const { return customerId; }
std::string Customer::getName() const { return name; }
std::string Customer::getPhone() const { return phone; }

void Customer::setName(const std::string& newName) { name = newName; }
void Customer::setPhone(const std::string& newPhone) { phone = newPhone; }

void Customer::display() const {
    std::cout << "Customer ID: " << customerId 
              << " | Name: " << name 
              << " | Phone: " << phone;
}