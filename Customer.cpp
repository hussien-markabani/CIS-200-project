#include "Customer.h"
#include <iostream>
#include <ctime>
using namespace std;

//Helper: returns customer index by name (or -1 if missing)

int CustomerDatabase::findCustomer(const string& name) const {
    for (int i = 0; i < customers.size(); i++) {
        if (customers[i].name == name) {
            return i;
        }
    }
    return -1;
}

//Helper: get current date & time

string CustomerDatabase::getCurrentDateTime() const {
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

//Add a new customer (only if not already stored)

void CustomerDatabase::addCustomer(const string& name) {
    if (findCustomer(name) != -1) {
        cout << "Customer already exists.\n";
        return;
    }

    Customer c;
    c.name = name;
    customers.push_back(c);
}

//Record a visit for a customer: Items, quantities, total spent, timestamp

void CustomerDatabase::recordVisit(const string& name, const vector<string>& items, const vector<int>& counts, double totalSpent) {
    int index = findCustomer(name);

    //Auto creates customer if missing
    if (index == -1) {
        cout << "Customer not found, adding new customer...\n";
        addCustomer(name);
        index = findCustomer(name);
    }
    Visit v;
    v.dateTime = getCurrentDateTime();
    v.items = items;
    v.counts = counts;
    v.totalSpent = totalSpent;

    customers[index].visits.push_back(v);
}

//Print all visits: items, quantities, money spent, date/time

void CustomerDatabase::getCustomerHistory(const string& name) const {
    int index = findCustomer(name);

    if (index == -1) {
        cout << "Customer not found.\n";
        return;
    }
    const Customer& c = customers[index];
    cout << "Purchase history for " << c.name << ":\n";

    if (c.visits.empty()) {
        cout << "No visits recorded.\n";
        return;
    }

    for (int i = 0; i < c.visits.size(); i++) {
        const Visit& v = c.visits[i];

        cout << "Visit #" << i + 1 << " on " << v.dateTime;
        cout << "Items purchased:\n";
        for (int j = 0; j < v.items.size(); j++) {
            cout << "  " << v.items[j] << " x" << v.counts[j] << "\n";
        }

        cout << "Total spent: $" << v.totalSpent << "\n\n";
    }

}