#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <string>

class Inventory;
class CustomerDatabase;

class FileManager {
public:
    // Inventory save/load
    static bool saveInventory(const Inventory& inventory,
                              const std::string& filename);

    static bool loadInventory(Inventory& inventory,
                              const std::string& filename);

    // Customer history save/load
    static bool saveCustomerHistory(const CustomerDatabase& db,
                                    const std::string& filename);

    static bool loadCustomerHistory(CustomerDatabase& db,
                                    const std::string& filename);
};

#endif // FILEMANAGER_H
