#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

class Customer {
private:
    string customerID;
    string fullName;
    string district;
    string category;
    double monthlyConsumption;
    double bill;
    int index;

public:
    Customer(int idx, string id, string name, string dist, string cat, double cons) {
        index = idx;
        customerID = id;
        fullName = name;
        district = dist;
        category = cat;
        monthlyConsumption = cons;
        bill = 0;
    }

    // Getters
    string getID() { return customerID; }
    string getName() { return fullName; }
    string getDistrict() { return district; }
    string getCategory() { return category; }
    double getConsumption() { return monthlyConsumption; }
    double getBill() { return bill; }
    int getIndex() { return index; }

    // Setters
    void setName(string name) { fullName = name; }
    void setCategory(string cat) { category = cat; }
    void setConsumption(double cons) { monthlyConsumption = cons; }

    void calculateBill() {
        if (category == "Residential")
            bill = monthlyConsumption * 183;
        else if (category == "Commercial")
            bill = monthlyConsumption * 214;
        else if (category == "Industrial")
            bill = monthlyConsumption * 198;
        else
            bill = 0;
    }

    void display() {
        cout << index << " | " << customerID << " | " << fullName << " | "
             << category << " | " << monthlyConsumption << " | " << bill << endl;
    }
};

// Validate category
bool validCategory(string cat) {
    return (cat == "Residential" || cat == "Commercial" || cat == "Industrial");
}

// Search customer
int findCustomer(vector<Customer> &c, string id) {
    for (int i = 0; i < c.size(); i++) {
        if (c[i].getID() == id)
            return i;
    }
    return -1;
}

// Save to file (YOUR REQUIRED FORMAT)
void saveToFile(vector<Customer> &c) {
    ofstream file("customers.txt");

    file << "ID\tFull Name\tCategory\tkWh/month\tIndex\n";

    for (auto &cust : c) {
        file << cust.getID() << "\t"
             << cust.getName() << "\t"
             << cust.getCategory() << "\t"
             << cust.getConsumption() << "\t"
             << cust.getIndex() << "\n";
    }

    file.close();
    cout << "Saved to customers.txt successfully!\n";
}

// Display all
void displayAll(vector<Customer> &c) {
    cout << "\nID | Name | Category | kWh | Bill\n";
    cout << "------------------------------------------\n";

    for (auto &cust : c) {
        cout << cust.getID() << " | "
             << cust.getName() << " | "
             << cust.getCategory() << " | "
             << cust.getConsumption() << " | "
             << cust.getBill() << endl;
    }
}

int main() {
    vector<Customer> customers;

    int n;
    cout << "Enter number of customers: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        string id, name, district, category;
        double cons;

        cout << "\nCustomer " << i + 1 << ":\n";

        cout << "ID: ";
        cin >> id;

        cin.ignore();
        cout << "Full Name: ";
        getline(cin, name);

        cout << "District: ";
        getline(cin, district);

        do {
            cout << "Category (Residential/Commercial/Industrial): ";
            cin >> category;
        } while (!validCategory(category));

        cout << "Consumption (kWh): ";
        cin >> cons;

        Customer c(i + 1, id, name, district, category, cons);
        c.calculateBill();
        customers.push_back(c);
    }

    int choice;

    do {
        cout << "\n==============================\n";
        cout << "RURA CUSTOMER SYSTEM\n";
        cout << "1. Display All\n";
        cout << "2. Search Customer\n";
        cout << "3. Edit Customer\n";
        cout << "4. Save to File\n";
        cout << "5. Exit\n";
        cout << "==============================\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            displayAll(customers);
        }

        else if (choice == 2) {
            string id;
            cout << "Enter ID: ";
            cin >> id;

            int pos = findCustomer(customers, id);

            if (pos != -1) {
                customers[pos].display();
            } else {
                cout << "Customer not found.\n";
            }
        }

        else if (choice == 3) {
            string id;
            cout << "Enter ID to edit: ";
            cin >> id;

            int pos = findCustomer(customers, id);

            if (pos != -1) {
                string name, category;
                double cons;

                cin.ignore();
                cout << "New Name: ";
                getline(cin, name);

                do {
                    cout << "New Category: ";
                    cin >> category;
                } while (!validCategory(category));

                cout << "New Consumption: ";
                cin >> cons;

                customers[pos].setName(name);
                customers[pos].setCategory(category);
                customers[pos].setConsumption(cons);
                customers[pos].calculateBill();

                cout << "Updated successfully!\n";
            } else {
                cout << "Customer not found.\n";
            }
        }

        else if (choice == 4) {
            saveToFile(customers);
        }

    } while (choice != 5);

    return 0;
}
