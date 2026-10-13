#ifndef BANK_H
#define BANK_H

#include "Account.h"
#include "FileManager.h"
#include <string>

class Bank {
private:
    std::string bankName;
    Account** accounts; // Dynamic memory pointer-to-pointer array
    int capacity;
    int count;
    FileManager fileManager;

    void resize();

public:
    Bank(const std::string& name = "SecureBank System", int initialCapacity = 5);
    ~Bank();

    // Menu operations
    void addRecord();
    void displayRecords() const;
    void searchRecord() const;
    void updateRecord();
    void deleteRecord();
    void mainTransaction();
    void generateReport() const;
    void saveRecords();
    void loadRecords();
};

#endif