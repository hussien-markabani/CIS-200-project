#include "Inventory.hpp"
#include<iostream>
#include<ctime>

//constructor
Inventory::Inventory(){
};

//function used to locate item index by name
int Inventory::findItem(const string& name) const {
    for (int i = 0; i < itemNames.size(); i++) {
        if (itemNames[i] == name)
            return static_cast<int>(i);
    }
    return -1;
}

//function to get current time and date
string Inventory::getCurrentDateTime() const {
    time_t now = time(0);
    char* dt = ctime(&now); // convert to string
    return string(dt);      // return as C++ string
}

// //function used to add items
void Inventory::addItem(const string&name, int count, double price){
    //fist check if the item in the inventory or not,if the item was found return index, if not it will return -1
    int index=findItem(name);
    
    if (index!=-1) {
        // If item already exists, update quantity and maybe price
        itemCounts[index]+=count;
        itemPrices[index]=price;
        return;
    } else {
        //adding new item
        itemNames.push_back(name);
        itemCounts.push_back(count);
        itemPrices.push_back(price);
    }
}

//function used to remove items
void Inventory:: removeItems(const string& name){
    int index=findItem(name);
    if (index==-1) {
        cout<<"sorry, there is no this kind of items in inventory."<<endl;
        return;
    } else {
        itemNames.erase(itemNames.begin()+index);
        itemCounts.erase(itemCounts.begin()+index);
        itemPrices.erase(itemPrices.begin()+index);
    }
}

//function used to sell item and then update the inventory
bool Inventory::checkoutItems(const string& name, int count){
    int index=findItem(name);
    if (index==-1) {
        cout<<"sorry,we do not have this item."<<endl;
        return false;
    }
    if (itemCounts[index]<count) {
        cout<<"sorry, fot this item we are out of stock right now."<<endl;
        return false;
    } else {
        itemCounts[index]-=count;
        return true;
    }
}

//function used to add quantity back when custormers return items
bool Inventory::returnItem(const string& name, int count){
    int index=findItem(name);
    if (index==-1) {
        cout<<"sorry,we do not have this item, can not be returned."<<endl;
        return false;
    } else {
        itemCounts[index] += count;
        return true;
    }
}
//function that used to check do we have enough of this item to sell right now
bool Inventory::isAvailable(const string& name, int count ) const{
    int index=findItem(name);
    if(index==-1)return false;
    return itemCounts[index] >=count;
}

//the fucntion used to print all items in the inventory
void Inventory::displayInventory() const {
    cout << "----- Inventory -----\n";
    for (int i = 0; i < itemNames.size(); i++) {
        cout << "Name: "  << itemNames[i]<<endl;
        cout<< " Count: " << itemCounts[i]<<endl;
        cout<< " Price: $" << itemPrices[i]<<endl;
    }
}
