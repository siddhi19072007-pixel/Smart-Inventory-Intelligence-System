#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// ==========================================================
// MEMBER 2: CUSTOMER, SALE & LINKED LIST ANALYTICS
// ==========================================================
class Customer {
private:
    int customerId;
    string name;
    string phone;

public:
    Customer(int cId = 0, string cName = "Walk-in", string cPhone = "N/A")
        : customerId(cId), name(cName), phone(cPhone) {}

    int getCustomerId() const { return customerId; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
};

class Sale {
private:
    int saleId;
    int productId;
    string productName;
    Customer customer;
    int quantitySold;
    double totalAmount;

public:
    Sale(int sId = 0, int pId = 0, string pName = "", Customer cust = Customer(), int qty = 0, double amt = 0.0)
        : saleId(sId), productId(pId), productName(pName), customer(cust), quantitySold(qty), totalAmount(amt) {}

    // Getters to read bill details (No setters to keep bills secure)
    int getSaleId() const { return saleId; }
    int getProductId() const { return productId; }
    string getProductName() const { return productName; }
    Customer getCustomer() const { return customer; }
    int getQuantity() const { return quantitySold; }
    double getTotalAmount() const { return totalAmount; }
};

// Singly Linked List Node
struct SaleNode {
    Sale saleData;       // Stores the bill object
    SaleNode* next;      // Points to the next bill in the list

    SaleNode(Sale s) : saleData(s), next(nullptr) {}
};

class SalesHistory {
private:
    SaleNode* head;      // First bill in the list
    SaleNode* tail;      // Last bill in the list
    int totalTransactions;

public:
    SalesHistory() : head(nullptr), tail(nullptr), totalTransactions(0) {}

    // Destructor: Frees memory when the program closes
    ~SalesHistory() {
        SaleNode* current = head;
        while (current != nullptr) {
            SaleNode* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = tail = nullptr;
    }

    // Adds a new bill at the end of the list in O(1) time
    void recordSale(Sale s) {
        SaleNode* newNode = new SaleNode(s);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        totalTransactions++;
    }

    // Prints all saved bills and total revenue
    void displayAllSales() const {
        if (head == nullptr) {
            cout << "\nNo sales transactions recorded yet.\n";
            return;
        }

        cout << "\n=========================================================================\n";
        cout << "                    SALES TRANSACTION LEDGER (LINKED LIST)               \n";
        cout << "=========================================================================\n";
        SaleNode* temp = head;
        double grandRevenue = 0.0;

        while (temp != nullptr) {
            cout << "Bill #" << temp->saleData.getSaleId()
                 << " | Item: " << temp->saleData.getProductName() << " (ID:" << temp->saleData.getProductId() << ")"
                 << " | Customer: " << temp->saleData.getCustomer().getName()
                 << " | Qty: " << temp->saleData.getQuantity()
                 << " | Amount: Rs." << temp->saleData.getTotalAmount() << "\n";
            grandRevenue += temp->saleData.getTotalAmount();
            temp = temp->next;
        }
        cout << "-------------------------------------------------------------------------\n";
        cout << "Total Bills: " << totalTransactions << " | Total Revenue Generated: Rs." << grandRevenue << "\n";
    }

    // Analytics: Calculates average units sold per day (Sales Velocity)
    double calculateSalesVelocity(int productId, int days) const {
        if (days <= 0) return 0.0;
        int totalUnits = 0;
        SaleNode* temp = head;

        while (temp != nullptr) {
            if (temp->saleData.getProductId() == productId) {
                totalUnits += temp->saleData.getQuantity();
            }
            temp = temp->next;
        }
        return (double)totalUnits / days;
    }

    // Counts total units sold for a specific product
    int getTotalUnitsSold(int productId) const {
        int units = 0;
        SaleNode* temp = head;
        while (temp != nullptr) {
            if (temp->saleData.getProductId() == productId) {
                units += temp->saleData.getQuantity();
            }
            temp = temp->next;
        }
        return units;
    }

    // Saves all sales records into a text file
    void exportSalesToFile(const string& filename) const {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Error creating report file.\n";
            return;
        }

        outFile << "=== SMART INVENTORY SYSTEM - SALES AUDIT REPORT ===\n";
        SaleNode* temp = head;
        while (temp != nullptr) {
            outFile << "Sale ID: " << temp->saleData.getSaleId()
                    << ", Product: " << temp->saleData.getProductName()
                    << ", Customer: " << temp->saleData.getCustomer().getName()
                    << ", Qty: " << temp->saleData.getQuantity()
                    << ", Total: Rs." << temp->saleData.getTotalAmount() << "\n";
            temp = temp->next;
        }
        outFile.close();
        cout << ">> [File Saved] Sales report exported to '" << filename << "'.\n";
    }
};
