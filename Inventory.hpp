#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>
using namespace std;

class Inventory {
private:
    vector<string> itemNames;   // dynamic list of item names
    vector<int> itemCounts;     // dynamic list of quantities
    vector<double> itemPrices;  // dynamic list of prices

    string getCurrentDateTime() const;

public:
    Inventory(); // constructor

    int findItem(const string& name) const;//function used to search an item(where is this item) by its name,it return the index of the item, it the item is not found, return -1.
    void addItem(const string& name, int count, double price);//function used to add items
    void removeItems(const string& name);//function used to remove items
    bool checkoutItems(const string& name, int count);//function used to sell item and then update the iinventory
    bool returnItem(const string& name, int count);//function used to add quantity back when custormers return items
    bool isAvailable(const string& name, int count = 1) const;//function that used to check do we have enough of this item to sell right now
    void displayInventory() const;//the fucntion used to print all items in the inventory
    
   
};

#endif

