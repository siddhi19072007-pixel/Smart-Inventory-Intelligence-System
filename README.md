# Smart Inventory Intelligence System

A modular C++ and Data Structures (DSA) application designed to automate inventory tracking, immutable customer billing, daily sales velocity analytics, and predictive supplier restocking—built using pure C++ without external STL containers.

## Project Architecture & Modules
- **Product Management (`src/product/Product.cpp`):** Product catalog management, encapsulation, and controlled stock updates.
- **Sales & Analytics (`src/sales/SalesHistory.cpp`):** Customer billing, custom pointer-based Singly Linked List (`head`/`tail` pointers), destructor memory management, daily sales velocity analytics, and file-based audit reporting.
- **Predictive Restocking (`src/restocking/Restocking.cpp`):** Automated restocking engine calculating lead-time demand and days-to-stockout alerts.
- **Supplier Directory (`src/supplier/Supplier.cpp`):** Approved vendor directory and delivery lead-time lookup.

## How to Compile & Run
```bash
g++ main.cpp -o inventory_system
./inventory_system
