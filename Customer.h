#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <vector>
using namespace std;

class CustomerDatabase {
    private:
        struct Visit {
            string dateTime;
            vector<string> items;
            vector<int> counts;
            double totalSpent;
        };

        struct Customer {
            string name;
            vector<Visit> visits;
        };

        vector<Customer> customers;

        int findCustomer(const string& name) const;
        string getCurrentDateTime() const;

    public:
        void addCustomer(const string& name);
        void recordVisit(const string& name, const vector<string>& items, const vector<int>& counts, double totalSpent);
        void getCustomerHistory(const string& name) const;
};


#endif