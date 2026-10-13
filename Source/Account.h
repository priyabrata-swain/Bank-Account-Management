#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "Customer.h"
#include "Transaction.h"
#include <string>
#include <iostream>

class Account {
protected:
    std::string accountNumber;
    Customer customer;
    double balance;
    
    // Dynamic array for account-level transaction history
    Transaction* transactions;
    int transactionCount;
    int transactionCapacity;

    void resizeTransactions();

public:
    Account();
    Account(const std::string& accNum, const Customer& cust, double initialBalance);
    virtual ~Account();

    std::string getAccountNumber() const;
    Customer getCustomer() const;
    double getBalance() const;
    void setCustomer(const Customer& cust);

    virtual void deposit(double amount);
    virtual void withdraw(double amount) = 0; // Pure virtual for polymorphism
    virtual std::string getAccountType() const = 0;
    virtual void display() const;

    void recordTransaction(const std::string& type, double amount);
    void printTransactionHistory() const;

    virtual std::string serialize() const;
};

#endif