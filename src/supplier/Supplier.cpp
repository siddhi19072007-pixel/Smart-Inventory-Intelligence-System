#include <iostream>
#include <string>

using namespace std;

const int MAX_SUPPLIERS = 20;

// ==========================================================
// MEMBER 4: SUPPLIER & VENDOR DIRECTORY
// ==========================================================
class Supplier {
private:
    int supplierId;
    string name;
    string contact;
    int leadTimeDays; // Days needed for delivery

public:
    Supplier(int id = 0, string n = "", string c = "", int days = 0)
        : supplierId(id), name(n), contact(c), leadTimeDays(days) {}

    // Getters to read supplier details
    int getId() const { return supplierId; }
    string getName() const { return name; }
    string getContact() const { return contact; }
    int getLeadTime() const { return leadTimeDays; }
};

// Finds a supplier's position in the array using their ID
int findSupplierIndex(const Supplier suppliers[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (suppliers[i].getId() == id) return i;
    }
    return -1;
}

void displaySuppliers(const Supplier suppliers[], int count) {
    cout << "\n=========================================================================\n";
    cout << "                       APPROVED SUPPLIER DIRECTORY                       \n";
    cout << "=========================================================================\n";
    cout << "ID\tVendor Name\t\tContact Number\tLead Time\n";
    for (int i = 0; i < count; i++) {
        cout << suppliers[i].getId() << "\t"
             << suppliers[i].getName() << "\t"
             << suppliers[i].getContact() << "\t"
             << suppliers[i].getLeadTime() << " days\n";
    }
}
