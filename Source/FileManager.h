#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Account.h"
#include <string>

class FileManager {
private:
    std::string filePath;

public:
    FileManager();
    FileManager(const std::string& path);
    ~FileManager();

    bool saveAccounts(Account** accounts, int count);
    bool loadAccounts(Account**& accounts, int& count, int& capacity);
};

#endif