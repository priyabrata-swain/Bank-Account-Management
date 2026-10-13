#include "FileManager.h"
#include "SavingsAccount.h"
#include <fstream>
#include <sstream>
#include <iostream>

FileManager::FileManager() : filePath("Data/accounts.txt") {}

FileManager::FileManager(const std::string& path) : filePath(path) {}

FileManager::~FileManager() {}

bool FileManager::saveAccounts(Account** accounts, int count) {
    std::ofstream outFile(filePath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filePath << "\n";
        return false;
    }

    for (int i = 0; i < count; ++i) {
        outFile << accounts[i]->serialize() << "\n";
    }

    outFile.close();
    return true;
}

bool FileManager::loadAccounts(Account**& accounts, int& count, int& capacity) {
    std::ifstream inFile(filePath);
    if (!inFile.is_open()) {
        return false; // File doesn't exist yet, clean start
    }

    // Free previously allocated memory
    for (int i = 0; i < count; ++i) {
        delete accounts[i];
    }
    delete[] accounts;

    capacity = 10;
    count = 0;
    accounts = new Account*[capacity];

    std::string line;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string accNum, custId, custName, custPhone;
        std::string balStr, rateStr, minBalStr;

        if (std::getline(ss, accNum, ',') &&
            std::getline(ss, custId, ',') &&
            std::getline(ss, custName, ',') &&
            std::getline(ss, custPhone, ',') &&
            std::getline(ss, balStr, ',') &&
            std::getline(ss, rateStr, ',') &&
            std::getline(ss, minBalStr, ',')) {

            double bal = std::stod(balStr);
            double rate = std::stod(rateStr);
            double minBal = std::stod(minBalStr);

            if (count == capacity) {
                capacity *= 2;
                Account** temp = new Account*[capacity];
                for (int i = 0; i < count; ++i) {
                    temp[i] = accounts[i];
                }
                delete[] accounts;
                accounts = temp;
            }

            Customer c(custId, custName, custPhone);
            accounts[count++] = new SavingsAccount(accNum, c, bal, rate, minBal);
        }
    }

    inFile.close();
    return true;
}