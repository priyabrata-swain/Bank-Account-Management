#include "Bank.h"
#include "SavingsAccount.h"
#include <iostream>
#include <iomanip>
#include <limits>

Bank::Bank(const std::string& name, int initialCapacity)
    : bankName(name), capacity(initialCapacity), count(0), fileManager("Data/accounts.txt") {
    accounts = new Account*[capacity];
    loadRecords();
}

Bank::~Bank() {
    saveRecords();
    for (int i = 0; i < count; ++i) {
        delete accounts[i];
    }
    delete[] accounts;
}

void Bank::resize() {
    capacity *= 2;
    Account** newArr = new Account*[capacity];
    for (int i = 0; i < count; ++i) {
        newArr[i] = accounts[i];
    }
    delete[] accounts;
    accounts = newArr;
}

void Bank::addRecord() {
    std::string accNum, custId, name, phone;
    double initialBal, minBal, rate;

    std::cout << "\n--- 1. Add New Account ---\n";
    std::cout << "Enter Account Number: ";
    std::cin >> accNum;

    for (int i = 0; i < count; ++i) {
        if (accounts[i]->getAccountNumber() == accNum) {
            std::cout << "Error: Account number already exists!\n";
            return;
        }
    }

    std::cout << "Enter Customer ID: ";
    std::cin >> custId;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter Customer Full Name: ";
    std::getline(std::cin, name);

    std::cout << "Enter Customer Phone: ";
    std::getline(std::cin, phone);

    std::cout << "Enter Minimum Balance Requirement ($): ";
    std::cin >> minBal;

    std::cout << "Enter Initial Balance ($): ";
    std::cin >> initialBal;

    std::cout << "Enter Annual Interest Rate (%): ";
    std::cin >> rate;

    try {
        if (count == capacity) {
            resize();
        }
        Customer c(custId, name, phone);
        accounts[count++] = new SavingsAccount(accNum, c, initialBal, rate, minBal);
        std::cout << "Account created successfully!\n";
    } catch (const std::exception& e) {
        std::cout << "Account creation failed: " << e.what() << "\n";
    }
}

void Bank::displayRecords() const {
    std::cout << "\n--- 2. All Bank Accounts ---\n";
    if (count == 0) {
        std::cout << "No accounts in the system.\n";
        return;
    }
    for (int i = 0; i < count; ++i) {
        accounts[i]->display();
    }
}

void Bank::searchRecord() const {
    std::string query;
    std::cout << "\n--- 3. Search Record ---\n";
    std::cout << "Enter Account Number or Customer Name: ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, query);

    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (accounts[i]->getAccountNumber() == query || 
            accounts[i]->getCustomer().getName() == query) {
            accounts[i]->display();
            accounts[i]->printTransactionHistory();
            found = true;
        }
    }
    if (!found) {
        std::cout << "No matching account found for: " << query << "\n";
    }
}

void Bank::updateRecord() {
    std::string accNum;
    std::cout << "\n--- 4. Update Account ---\n";
    std::cout << "Enter Account Number to update: ";
    std::cin >> accNum;

    for (int i = 0; i < count; ++i) {
        if (accounts[i]->getAccountNumber() == accNum) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string newName, newPhone;

            std::cout << "Enter New Name: ";
            std::getline(std::cin, newName);

            std::cout << "Enter New Phone: ";
            std::getline(std::cin, newPhone);

            Customer cust = accounts[i]->getCustomer();
            if (!newName.empty()) cust.setName(newName);
            if (!newPhone.empty()) cust.setPhone(newPhone);
            accounts[i]->setCustomer(cust);

            std::cout << "Account updated successfully.\n";
            return;
        }
    }
    std::cout << "Account not found.\n";
}

void Bank::deleteRecord() {
    std::string accNum;
    std::cout << "\n--- 5. Delete Account ---\n";
    std::cout << "Enter Account Number to delete: ";
    std::cin >> accNum;

    int foundIndex = -1;
    for (int i = 0; i < count; ++i) {
        if (accounts[i]->getAccountNumber() == accNum) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex != -1) {
        delete accounts[foundIndex];
        for (int i = foundIndex; i < count - 1; ++i) {
            accounts[i] = accounts[i + 1];
        }
        --count;
        std::cout << "Account " << accNum << " deleted successfully.\n";
    } else {
        std::cout << "Account not found.\n";
    }
}

void Bank::mainTransaction() {
    std::string accNum;
    int opt;
    double amount;

    std::cout << "\n--- 6. Main Transaction / Process ---\n";
    std::cout << "Enter Account Number: ";
    std::cin >> accNum;

    Account* target = nullptr;
    for (int i = 0; i < count; ++i) {
        if (accounts[i]->getAccountNumber() == accNum) {
            target = accounts[i];
            break;
        }
    }

    if (!target) {
        std::cout << "Account not found.\n";
        return;
    }

    std::cout << "Current Balance: $" << std::fixed << std::setprecision(2) << target->getBalance() << "\n";
    std::cout << "1. Deposit\n";
    std::cout << "2. Withdraw\n";
    std::cout << "3. Apply Annual Interest (Savings Feature)\n";
    std::cout << "Select Operation: ";
    std::cin >> opt;

    try {
        if (opt == 1) {
            std::cout << "Enter deposit amount: $";
            std::cin >> amount;
            target->deposit(amount);
            std::cout << "Deposit successful! New Balance: $" << target->getBalance() << "\n";
        } else if (opt == 2) {
            std::cout << "Enter withdrawal amount: $";
            std::cin >> amount;
            target->withdraw(amount);
            std::cout << "Withdrawal successful! New Balance: $" << target->getBalance() << "\n";
        } else if (opt == 3) {
            SavingsAccount* sa = dynamic_cast<SavingsAccount*>(target);
            if (sa) {
                sa->applyInterest();
            } else {
                std::cout << "Operation not supported for this account type.\n";
            }
        } else {
            std::cout << "Invalid transaction type selected.\n";
        }
    } catch (const std::exception& e) {
        std::cout << "Transaction Error: " << e.what() << "\n";
    }
}

void Bank::generateReport() const {
    std::cout << "\n=======================================================\n";
    std::cout << "              BANK FINANCIAL SUMMARY REPORT            \n";
    std::cout << "=======================================================\n";
    std::cout << "Total Active Accounts: " << count << "\n";

    double totalDeposits = 0.0;
    double maxBalance = -1.0;
    std::string richestHolder = "N/A";

    for (int i = 0; i < count; ++i) {
        double b = accounts[i]->getBalance();
        totalDeposits += b;
        if (b > maxBalance) {
            maxBalance = b;
            richestHolder = accounts[i]->getCustomer().getName();
        }
    }

    std::cout << "Total Funds Held:      $" << std::fixed << std::setprecision(2) << totalDeposits << "\n";
    if (count > 0) {
        std::cout << "Average Account Value: $" << (totalDeposits / count) << "\n";
        std::cout << "Highest Balance:       $" << maxBalance << " (" << richestHolder << ")\n";
    }
    std::cout << "=======================================================\n";
}

void Bank::saveRecords() {
    if (fileManager.saveAccounts(accounts, count)) {
        std::cout << "System data successfully persisted to Data/accounts.txt\n";
    } else {
        std::cout << "Failed to persist data.\n";
    }
}

void Bank::loadRecords() {
    if (fileManager.loadAccounts(accounts, count, capacity)) {
        std::cout << "Loaded " << count << " record(s) from Data/accounts.txt\n";
    } else {
        std::cout << "No previous data file found; initializing fresh system state.\n";
    }
}