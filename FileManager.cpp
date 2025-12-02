#include "FileManager.h"

#include "Inventory.hpp"
#include "Customer.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

using std::string;
using std::vector;


static vector<string> split(const string& line, char delim) {
    vector<string> parts;
    std::stringstream ss(line);
    string token;

    while (std::getline(ss, token, delim)) {
        parts.push_back(token);
    }
    return parts;
}

bool FileManager::saveInventory(const Inventory& inventory,
                                const string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error: could not open " << filename << " for writing.\n";
        return false;
    }

    // header row
    out << "name,count,price\n";

    
    for (size_t i = 0; i < inventory.itemNames.size(); ++i) {
        out << inventory.itemNames[i] << ","
            << inventory.itemCounts[i] << ","
            << inventory.itemPrices[i] << "\n";
    }

    return true;
}

bool FileManager::loadInventory(Inventory& inventory,
                                const string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Warning: could not open " << filename
                  << " for reading. Starting with empty inventory.\n";
        return false;
    }

    // clear current data
    inventory.itemNames.clear();
    inventory.itemCounts.clear();
    inventory.itemPrices.clear();

    string line;

    // Skip header
    if (!std::getline(in, line)) {
        return false; // if file was empty
    }

    
    while (std::getline(in, line)) {
        if (line.empty()) continue;

        vector<string> parts = split(line, ',');
        if (parts.size() != 3) {
            // if bad line format, just skip
            continue;
        }

        string name   = parts[0];
        int count     = std::stoi(parts[1]);
        double price  = std::stod(parts[2]);

        inventory.itemNames.push_back(name);
        inventory.itemCounts.push_back(count);
        inventory.itemPrices.push_back(price);
    }

    return true;
}

bool FileManager::saveCustomerHistory(const CustomerDatabase& db,
                                      const string& filename) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        std::cerr << "Error: could not open " << filename << " for writing.\n";
        return false;
    }

    out << "customerName,dateTime,items,counts,totalSpent\n";

    
    for (const auto& customer : db.customers) {
        for (const auto& visit : customer.visits) {

            
            string itemsStr;
            for (size_t i = 0; i < visit.items.size(); ++i) {
                if (i > 0) itemsStr += '|';
                itemsStr += visit.items[i];
            }

            
            string countsStr;
            for (size_t i = 0; i < visit.counts.size(); ++i) {
                if (i > 0) countsStr += '|';
                countsStr += std::to_string(visit.counts[i]);
            }

            out << customer.name      << ","
                << visit.dateTime     << ","
                << itemsStr           << ","
                << countsStr          << ","
                << visit.totalSpent   << "\n";
        }
    }

    return true;
}

bool FileManager::loadCustomerHistory(CustomerDatabase& db,
                                      const string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Warning: could not open " << filename
                  << " for reading. Starting with empty customers.\n";
        return false;
    }

    db.customers.clear();
    string line;

    
    if (!std::getline(in, line)) {
        return false;
    }

    while (std::getline(in, line)) {
        if (line.empty()) continue;

        vector<string> parts = split(line, ',');
        if (parts.size() != 5) {
            continue;
        }

        string name       = parts[0];
        string dateTime   = parts[1];
        vector<string> itemTokens  = split(parts[2], '|');
        vector<string> countTokens = split(parts[3], '|');
        double totalSpent = std::stod(parts[4]);

       
        int customerIndex = -1;
        for (size_t i = 0; i < db.customers.size(); ++i) {
            if (db.customers[i].name == name) {
                customerIndex = static_cast<int>(i);
                break;
            }
        }

        // if not found, create a new customer
        if (customerIndex == -1) {
            CustomerDatabase::Customer newCustomer;
            newCustomer.name = name;
            db.customers.push_back(newCustomer);
            customerIndex = static_cast<int>(db.customers.size() - 1);
        }

        
        CustomerDatabase::Visit visit;
        visit.dateTime = dateTime;
        visit.items = itemTokens;

        for (const auto& cStr : countTokens) {
            visit.counts.push_back(std::stoi(cStr));
        }

        visit.totalSpent = totalSpent;

        db.customers[customerIndex].visits.push_back(visit);
    }

    return true;
}
