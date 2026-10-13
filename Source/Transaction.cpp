#include "Transaction.h"
#include <iomanip>

Transaction::Transaction() : transactionId(""), type(""), amount(0.0), timestamp("") {}

Transaction::Transaction(const std::string& id, const std::string& type, double amount, const std::string& timestamp)
    : transactionId(id), type(type), amount(amount), timestamp(timestamp) {}

Transaction::~Transaction() {}

std::string Transaction::getId() const { return transactionId; }
std::string Transaction::getType() const { return type; }
double Transaction::getAmount() const { return amount; }
std::string Transaction::getTimestamp() const { return timestamp; }

void Transaction::display() const {
    std::cout << "[" << timestamp << "] " 
              << "ID: " << transactionId 
              << " | " << std::left << std::setw(12) << type 
              << " | Amount: $" << std::fixed << std::setprecision(2) << amount << "\n";
}