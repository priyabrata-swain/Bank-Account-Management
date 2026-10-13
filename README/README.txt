========================================================================
PROJECT CODE: CPP18 - BANK ACCOUNT MANAGEMENT SYSTEM
STUDENT ENROLLMENT: IU2541230440
========================================================================

1. PROJECT OVERVIEW
------------------------------------------------------------------------
A comprehensive Bank Account Management system developed in C++ (C++17) 
demonstrating Object-Oriented Programming (OOP) principles, dynamic memory 
management, runtime polymorphism, and persistent file I/O.

2. FOLDER STRUCTURE
------------------------------------------------------------------------
- Source/      : Modular C++ header (.h) and implementation (.cpp) files
- Data/        : Persistent storage (accounts.txt)
- Diagrams/    : PlantUML source scripts (.puml) and exported diagrams (.png)
- Executable/  : Compiled binary (Project.exe)
- Screenshots/ : Visual execution logs of all 9 menu operations
- README.txt   : Project setup and instructions
- ProjectReport.pdf : Complete project documentation

3. HOW TO COMPILE
------------------------------------------------------------------------
From the root directory, run:
g++ -std=c++17 Source/*.cpp -o Executable/Project.exe

4. HOW TO RUN
------------------------------------------------------------------------
Windows:
.\Executable\Project.exe

macOS / Linux:
./Executable/Project

5. MENU OPERATIONS IMPLEMENTED
------------------------------------------------------------------------
1. Add Record (Account & Customer registration)
2. Display Records (Tabular display of accounts)
3. Search Record (By Account Number or Holder Name with Transaction History)
4. Update Record (Modify Customer details)
5. Delete Record (Account closure with memory deallocation)
6. Main Transaction (Deposit, Withdrawal with minimum balance check, Interest calculation)
7. Report (Financial totals, averages, and peak metrics)
8. Save / Load (File persistence with Data/accounts.txt)
9. Exit (Automatic save upon termination via RAII)