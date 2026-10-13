#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <iostream>

class Transaction {
private:
    std::string transactionId;
    std::string type; // "DEPOSIT", "WITHDRAWAL", "INTEREST"
    double amount;
    std::string timestamp;

public:
    Transaction();
    Transaction(const std::string& id, const std::string& type, double amount, const std::string& timestamp);
    ~Transaction();

    std::string getId() const;
    std::string getType() const;
    double getAmount() const;
    std::string getTimestamp() const;

    void display() const;
};

#endif