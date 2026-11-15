#include <iostream>
#include <fstream>
#include <string>
#include <limits>

using namespace std;

const int MAX_PRODUCTS = 100;
const int MAX_SUPPLIERS = 20;

// ==========================================================
// 1. SUPPLIER CLASS (Member 4)
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

// ==========================================================
// 2. PRODUCT CLASS (Member 1)
// ==========================================================
class Product {
private:
    int id;
    string name;
    double unitPrice;
    int stockQuantity;
    int expectedDailySales;
    int supplierId;

public:
    Product(int pId = 0, string pName = "", double price = 0.0, int stock = 0, int daily = 0, int supId = 0)
        : id(pId), name(pName), unitPrice(price), stockQuantity(stock), expectedDailySales(daily), supplierId(supId) {}

    // Getters to read product details
    int getId() const { return id; }
    string getName() const { return name; }
    double getPrice() const { return unitPrice; }
    int getStock() const { return stockQuantity; }
    int getExpectedDailySales() const { return expectedDailySales; }
    int getSupplierId() const { return supplierId; }

    // Reduces stock when an item is sold
    bool reduceStock(int qty) {
        if (qty <= 0 || qty > stockQuantity) return false;
        stockQuantity -= qty;
        return true;
    }

    // Increases stock when new supply arrives
    void addStock(int qty) {
        if (qty > 0) stockQuantity += qty;
    }
};

// ==========================================================
// 3. CUSTOMER & SALE CLASSES (Member 2 - OOP Part)
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

// ==========================================================
// 4. LINKED LIST FOR SALES HISTORY (Member 2 - DSA Part)
// ==========================================================
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

// ==========================================================
// 5. HELPER FUNCTIONS (Search & Display)
// ==========================================================
// Finds a product's position in the array using its ID
int findProductIndex(const Product products[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (products[i].getId() == id) return i;
    }
    return -1;
}

// Finds a supplier's position in the array using their ID
int findSupplierIndex(const Supplier suppliers[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (suppliers[i].getId() == id) return i;
    }
    return -1;
}

void displayInventory(const Product products[], int count) {
    cout << "\n=========================================================================\n";
    cout << "                         LIVE INVENTORY CATALOG                          \n";
    cout << "=========================================================================\n";
    cout << "ID\tProduct Name\t\tPrice\tStock\tEst.Daily\tSupplier ID\n";
    for (int i = 0; i < count; i++) {
        cout << products[i].getId() << "\t"
             << products[i].getName() << "\t\tRs."
             << products[i].getPrice() << "\t"
             << products[i].getStock() << "\t"
             << products[i].getExpectedDailySales() << "\t\t"
             << products[i].getSupplierId() << "\n";
    }
}

void addNewProduct(Product products[], int& count) {
    if (count >= MAX_PRODUCTS) {
        cout << "Inventory capacity full.\n";
        return;
    }
    int id, stock, daily, supId;
    double price;
    string name;

    cout << "\nEnter New Product ID: ";
    cin >> id;
    if (findProductIndex(products, count, id) != -1) {
        cout << "Error: Product ID already exists.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Product Name: ";
    getline(cin, name);
    cout << "Enter Unit Price (Rs.): ";
    cin >> price;
    cout << "Enter Initial Stock Quantity: ";
    cin >> stock;
    cout << "Enter Expected Daily Sales: ";
    cin >> daily;
    cout << "Enter Supplier ID (1 or 2): ";
    cin >> supId;

    products[count++] = Product(id, name, price, stock, daily, supId);
    cout << ">> Product added to inventory successfully!\n";
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

// ==========================================================
// 6. RESTOCK ALERTS ENGINE (Member 3)
// ==========================================================
void runIntelligentRestockEngine(const Product products[], int pCount,
                                 const Supplier suppliers[], int sCount,
                                 const SalesHistory& salesLog, int analysisDays) {
    cout << "\n=========================================================================\n";
    cout << "               INTELLIGENT RESTOCK & STOCK-OUT PREDICTOR                 \n";
    cout << "=========================================================================\n";

    bool anyAlert = false;
    for (int i = 0; i < pCount; i++) {
        int pId = products[i].getId();
        int currentStock = products[i].getStock();

        // Get actual sales speed from Member 2's sales history
        double actualVelocity = salesLog.calculateSalesVelocity(pId, analysisDays);
        double effectiveVelocity = (actualVelocity > 0) ? actualVelocity : products[i].getExpectedDailySales();

        // Get supplier contact and delivery days from Member 4
        int sIdx = findSupplierIndex(suppliers, sCount, products[i].getSupplierId());
        int leadTime = (sIdx != -1) ? suppliers[sIdx].getLeadTime() : 5;
        string vendorName = (sIdx != -1) ? suppliers[sIdx].getName() : "Default Vendor";
        string vendorPhone = (sIdx != -1) ? suppliers[sIdx].getContact() : "N/A";

        // Calculate stock needed while waiting for delivery
        double leadTimeDemand = effectiveVelocity * leadTime;
        double daysLeft = (effectiveVelocity > 0) ? (currentStock / effectiveVelocity) : 999.0;

        // Show alert if current stock is too low
        if (currentStock <= leadTimeDemand) {
            anyAlert = true;
            int recommendedOrder = (int)(leadTimeDemand * 2) - currentStock;
            if (recommendedOrder < 10) recommendedOrder = 20;

            cout << "[HIGH PRIORITY RESTOCK] " << products[i].getName() << " (ID: " << pId << ")\n"
                 << "  -> Current Stock: " << currentStock << " units | Est. Days Left: " << (int)daysLeft << " days\n"
                 << "  -> Sales Velocity: " << effectiveVelocity << " units/day | Lead Time: " << leadTime << " days\n"
                 << "  -> Action: Order " << recommendedOrder << " units from " << vendorName
                 << " (Contact: " << vendorPhone << ")\n\n";
        }
    }

    if (!anyAlert) {
        cout << "All inventory levels are optimal. No immediate restocking needed.\n";
    }
}

// ==========================================================
// 7. MAIN PROGRAM (Starts Execution Here)
// ==========================================================
int main() {
    // Load initial suppliers
    Supplier suppliers[MAX_SUPPLIERS] = {
        Supplier(1, "Apex Pharma Dist.", "9876543210", 4),
        Supplier(2, "MedLife Logistics", "9123456789", 3)
    };
    int supplierCount = 2;

    // Load initial products
    Product products[MAX_PRODUCTS] = {
        Product(101, "Paracetamol 500", 50.0, 30, 8, 1),
        Product(102, "Amoxicillin Cap", 120.0, 90, 5, 1),
        Product(103, "Cough Syrup    ", 85.0, 12, 4, 2),
        Product(104, "Vitamin D3 Tabs", 150.0, 60, 6, 2)
    };
    int productCount = 4;

    // Setup sales history manager
    SalesHistory salesLog;
    int nextSaleId = 1001;
    int nextCustId = 1;
    int analysisPeriodDays = 5;

    // Add 3 sample sales for demo
    salesLog.recordSale(Sale(nextSaleId++, 101, "Paracetamol 500", Customer(nextCustId++, "Rohan Sharma", "9811001122"), 15, 750.0));
    salesLog.recordSale(Sale(nextSaleId++, 101, "Paracetamol 500", Customer(nextCustId++, "Priya Verma", "9822003344"), 20, 1000.0));
    salesLog.recordSale(Sale(nextSaleId++, 103, "Cough Syrup    ", Customer(nextCustId++, "Amit Negi", "9833005566"), 10, 850.0));

    int choice;
    do {
        cout << "\n==========================================================\n";
        cout << "     SMART INVENTORY INTELLIGENCE SYSTEM (FINAL 100%)     \n";
        cout << "==========================================================\n";
        cout << "1. View Live Inventory (Member 1)\n";
        cout << "2. Add New Product to Catalog (Member 1)\n";
        cout << "3. Process Customer Sale & Auto-Deduct Stock (Member 1 + 2)\n";
        cout << "4. View Complete Sales Ledger & Revenue (Member 2)\n";
        cout << "5. Check Product Sales Velocity Analytics (Member 2)\n";
        cout << "6. Run Intelligent Restock & Vendor Alert Engine (All 4)\n";
        cout << "7. View Supplier Directory (Member 4)\n";
        cout << "8. Restock Existing Product Manually (Member 1 + 4)\n";
        cout << "9. Export Sales Audit Report to File (Member 2)\n";
        cout << "0. Exit System\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a valid number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                displayInventory(products, productCount);
                break;

            case 2:
                addNewProduct(products, productCount);
                break;

            case 3: {
                int pId, qty;
                string cName, cPhone;

                cout << "\n--- New Customer Billing ---\n";
                cout << "Enter Product ID: ";
                cin >> pId;

                int idx = findProductIndex(products, productCount, pId);
                if (idx == -1) {
                    cout << "Error: Product ID not found.\n";
                    break;
                }

                cout << "Selected: " << products[idx].getName()
                     << " | Available Stock: " << products[idx].getStock()
                     << " | Price: Rs." << products[idx].getPrice() << "\n";
                cout << "Enter Quantity to Purchase: ";
                cin >> qty;

                // Check and reduce stock
                if (!products[idx].reduceStock(qty)) {
                    cout << "Transaction Failed: Insufficient stock or invalid quantity.\n";
                    break;
                }

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter Customer Name: ";
                getline(cin, cName);
                cout << "Enter Customer Phone: ";
                getline(cin, cPhone);

                double billAmount = qty * products[idx].getPrice();
                Customer cust(nextCustId++, cName, cPhone);
                Sale newSale(nextSaleId++, pId, products[idx].getName(), cust, qty, billAmount);

                // Save bill to the Linked List
                salesLog.recordSale(newSale);
                cout << ">> [Billing Complete] Bill #" << newSale.getSaleId()
                     << " | Total: Rs." << billAmount
                     << " | Remaining Stock: " << products[idx].getStock() << "\n";
                break;
            }

            case 4:
                salesLog.displayAllSales();
                break;

            case 5: {
                int pId;
                cout << "\nEnter Product ID for Analytics: ";
                cin >> pId;
                int idx = findProductIndex(products, productCount, pId);
                if (idx == -1) {
                    cout << "Product ID not found.\n";
                    break;
                }
                int sold = salesLog.getTotalUnitsSold(pId);
                double velocity = salesLog.calculateSalesVelocity(pId, analysisPeriodDays);
                cout << "\n--- Sales Velocity Report (" << analysisPeriodDays << "-Day Window) ---\n";
                cout << "Product: " << products[idx].getName() << "\n";
                cout << "Total Units Sold: " << sold << " units\n";
                cout << "Actual Sales Velocity: " << velocity << " units/day\n";
                break;
            }

            case 6:
                runIntelligentRestockEngine(products, productCount, suppliers, supplierCount, salesLog, analysisPeriodDays);
                break;

            case 7:
                displaySuppliers(suppliers, supplierCount);
                break;

            case 8: {
                int pId, addQty;
                cout << "\nEnter Product ID to Restock: ";
                cin >> pId;
                int idx = findProductIndex(products, productCount, pId);
                if (idx == -1) {
                    cout << "Product not found.\n";
                    break;
                }
                cout << "Enter Quantity Received from Supplier: ";
                cin >> addQty;
                products[idx].addStock(addQty);
                cout << ">> Stock Updated! New Stock for " << products[idx].getName()
                     << ": " << products[idx].getStock() << " units.\n";
                break;
            }

            case 9:
                salesLog.exportSalesToFile("sales_report.txt");
                break;

            case 0:
                cout << "\nCleaning up dynamic memory (Destructor called)... Exiting system.\n";
                break;

            default:
                cout << "Invalid choice. Please select between 0 and 9.\n";
        }
    } while (choice != 0);

    return 0;
}
