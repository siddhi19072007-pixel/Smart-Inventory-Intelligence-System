#include <iostream>
#include <string>
#include <limits>

using namespace std;

const int MAX_PRODUCTS = 100;

// ==========================================================
// MEMBER 1: PRODUCT & INVENTORY MANAGEMENT
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

// Finds a product's position in the array using its ID
int findProductIndex(const Product products[], int count, int id) {
    for (int i = 0; i < count; i++) {
        if (products[i].getId() == id) return i;
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
