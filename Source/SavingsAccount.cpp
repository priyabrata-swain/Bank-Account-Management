#include "SavingsAccount.h"
#include <iomanip>
#include <stdexcept>
#include <sstream>

SavingsAccount::SavingsAccount() 
    : Account(), interestRate(4.0), minBalance(500.0) {}

SavingsAccount::SavingsAccount(const std::string& accNum, const Customer& cust, double initialBalance, 
                               double rate, double minBal)
    : Account(accNum, cust, initialBalance), interestRate(rate), minBalance(minBal) {
    if (initialBalance < minBal) {
        throw std::invalid_argument("Initial balance cannot be below minimum balance requirement ($" + std::to_string(minBal) + ").");
    }
}

SavingsAccount::~SavingsAccount() {}

double SavingsAccount::getInterestRate() const { return interestRate; }
double SavingsAccount::getMinBalance() const { return minBalance; }

void SavingsAccount::setInterestRate(double rate) { interestRate = rate; }
void SavingsAccount::setMinBalance(double minBal) { minBalance = minBal; }

void SavingsAccount::withdraw(double amount) {
    if (amount <= 0.0) {
        throw std::invalid_argument("Withdrawal amount must be greater than zero.");
    }
    if (balance - amount < minBalance) {
        throw std::runtime_error("Withdrawal denied: Account balance cannot drop below minimum balance ($" + std::to_string(minBalance) + ").");
    }
    balance -= amount;
    recordTransaction("WITHDRAWAL", amount);
}

void SavingsAccount::applyInterest() {
    double interest = balance * (interestRate / 100.0);
    balance += interest;
    recordTransaction("INTEREST", interest);
    std::cout << "Interest of $" << std::fixed << std::setprecision(2) << interest << " applied successfully.\n";
}

std::string SavingsAccount::getAccountType() const {
    return "Savings";
}

void SavingsAccount::display() const {
    Account::display();
    std::cout << " | Type: Savings" 
              << " | MinBal: $" << std::fixed << std::setprecision(2) << minBalance
              << " | IntRate: " << interestRate << "%\n";
}

std::string SavingsAccount::serialize() const {
    std::ostringstream oss;
    oss << Account::serialize() << "," << interestRate << "," << minBalance;
    return oss.str();
}