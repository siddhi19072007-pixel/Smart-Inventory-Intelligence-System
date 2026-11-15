#include <iostream>
#include <string>

using namespace std;

// ==========================================================
// MEMBER 3: INTELLIGENT RESTOCKING & STOCK-OUT PREDICTOR
// Connects Product Stock, Sales Velocity & Supplier Lead Time
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
