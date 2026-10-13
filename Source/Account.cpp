#include "Account.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>

Account::Account() 
    : accountNumber(""), customer(), balance(0.0), transactionCount(0), transactionCapacity(5) {
    transactions = new Transaction[transactionCapacity];
}

Account::Account(const std::string& accNum, const Customer& cust, double initialBalance)
    : accountNumber(accNum), customer(cust), balance(initialBalance), transactionCount(0), transactionCapacity(5) {
    if (initialBalance < 0.0) {
        throw std::invalid_argument("Initial balance cannot be negative.");
    }
    transactions = new Transaction[transactionCapacity];
}

Account::~Account() {
    delete[] transactions;
}

void Account::resizeTransactions() {
    transactionCapacity *= 2;
    Transaction* newArr = new Transaction[transactionCapacity];
    for (int i = 0; i < transactionCount; ++i) {
        newArr[i] = transactions[i];
    }
    delete[] transactions;
    transactions = newArr;
}

std::string Account::getAccountNumber() const { return accountNumber; }
Customer Account::getCustomer() const { return customer; }
double Account::getBalance() const { return balance; }
void Account::setCustomer(const Customer& cust) { customer = cust; }

void Account::deposit(double amount) {
    if (amount <= 0.0) {
        throw std::invalid_argument("Deposit amount must be greater than zero.");
    }
    balance += amount;
    recordTransaction("DEPOSIT", amount);
}

void Account::recordTransaction(const std::string& type, double amount) {
    if (transactionCount == transactionCapacity) {
        resizeTransactions();
    }
    std::time_t now = std::time(nullptr);
    char buf[20];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M", std::localtime(&now));
    
    std::string tId = "TXN" + std::to_string(transactionCount + 101);
    transactions[transactionCount++] = Transaction(tId, type, amount, std::string(buf));
}

void Account::printTransactionHistory() const {
    std::cout << "\n--- Transaction History for Account: " << accountNumber << " ---\n";
    if (transactionCount == 0) {
        std::cout << "No transactions recorded yet.\n";
        return;
    }
    for (int i = 0; i < transactionCount; ++i) {
        transactions[i].display();
    }
}

void Account::display() const {
    std::cout << "Acc No: " << std::setw(10) << std::left << accountNumber
              << " | Holder: " << std::setw(15) << std::left << customer.getName()
              << " | Balance: $" << std::setw(10) << std::fixed << std::setprecision(2) << balance;
}

std::string Account::serialize() const {
    std::ostringstream oss;
    oss << accountNumber << "," 
        << customer.getId() << "," 
        << customer.getName() << "," 
        << customer.getPhone() << "," 
        << balance;
    return oss.str();
}