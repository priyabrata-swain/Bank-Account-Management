#include "Bank.h"
#include <iostream>
#include <limits>

void printMenu() {
    std::cout << "\n=======================================\n";
    std::cout << "    BANK ACCOUNT MANAGEMENT SYSTEM     \n";
    std::cout << "=======================================\n";
    std::cout << "1. Add Record\n";
    std::cout << "2. Display Records\n";
    std::cout << "3. Search Record\n";
    std::cout << "4. Update Record\n";
    std::cout << "5. Delete Record\n";
    std::cout << "6. Main Transaction / Process\n";
    std::cout << "7. Report\n";
    std::cout << "8. Save / Load\n";
    std::cout << "9. Exit\n";
    std::cout << "=======================================\n";
    std::cout << "Enter your choice (1-9): ";
}

int main() {
    Bank bankSystem("National Bank", 5);
    int choice = 0;

    while (true) {
        printMenu();
        if (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a number between 1 and 9.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                bankSystem.addRecord();
                break;
            case 2:
                bankSystem.displayRecords();
                break;
            case 3:
                bankSystem.searchRecord();
                break;
            case 4:
                bankSystem.updateRecord();
                break;
            case 5:
                bankSystem.deleteRecord();
                break;
            case 6:
                bankSystem.mainTransaction();
                break;
            case 7:
                bankSystem.generateReport();
                break;
            case 8: {
                int sl;
                std::cout << "1. Save Records to File\n2. Reload Records from File\nChoice: ";
                std::cin >> sl;
                if (sl == 1) bankSystem.saveRecords();
                else if (sl == 2) bankSystem.loadRecords();
                else std::cout << "Invalid choice.\n";
                break;
            }
            case 9:
                std::cout << "Exiting application. Saving data...\n";
                return 0; // Bank destructor automatically persists data
            default:
                std::cout << "Invalid option. Please choose between 1 and 9.\n";
                break;
        }
    }

    return 0;
}