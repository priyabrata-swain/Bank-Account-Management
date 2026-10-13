#ifndef SAVINGSACCOUNT_H
#define SAVINGSACCOUNT_H

#include "Account.h"

class SavingsAccount : public Account {
private:
    double interestRate; // Annual percentage (e.g., 4.5)
    double minBalance;   // Minimum balance threshold

public:
    SavingsAccount();
    SavingsAccount(const std::string& accNum, const Customer& cust, double initialBalance, 
                   double rate = 4.0, double minBal = 500.0);
    ~SavingsAccount() override;

    double getInterestRate() const;
    double getMinBalance() const;

    void setInterestRate(double rate);
    void setMinBalance(double minBal);

    void withdraw(double amount) override;
    void applyInterest();

    std::string getAccountType() const override;
    void display() const override;
    std::string serialize() const override;
};

#endif