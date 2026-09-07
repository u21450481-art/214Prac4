// Base Abstractions & Interfaces
#include "ShippingComponent.h"
#include "Iterator.h"
#include "PackageState.h"

// Concrete Iterators
#include "BFSIterator.h"
#include "DestinationIterator.h"
#include "CostFilterIterator.h"

// Composite Hierarchy
#include "ShipmentGroup.h"
#include "Package.h"

// Decorators
#include "PackageDecorator.h"
#include "Fragile.h"
#include "Hazardous.h"
#include "Refridgerated.h"

// State Pattern & Context
#include "PackageJourney.h"
#include "NotDelivered.h"
#include "OnRoute.h"
#include "Delayed.h"
#include "Delivered.h"

// Standard Library
#include <iostream>
#include <vector>
#include <queue>
#include <string>

// --- Color Constants ---
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";

void goBackToMenu()
{
    std::cout << BOLD << MAGENTA << "\n[Press Enter to return to menu...]" << RESET;
    std::cin.ignore(10000, '\n');
}

void printShippingComponent(ShippingComponent *node)
{
    std::cout << "  * " << CYAN << node->getDestination() << RESET
              << " | " << node->getWeight() << " kg"
              << " | Cost: " << GREEN << "R" << node->getCost() << RESET
              << " | Est: " << YELLOW << node->getDeliveryTime() << " days" << RESET
              << std::endl;
}

void printComponentInfo(const std::string &label, ShippingComponent *component)
{
    std::cout << "\n"
              << BOLD << MAGENTA << "=== " << label << " ===" << RESET << "\n";
    std::cout << "Destination: " << CYAN << component->getDestination() << RESET << "\n";
    std::cout << "Weight: " << component->getWeight() << " kg\n";
    std::cout << "Cost: " << GREEN << "R" << component->getCost() << RESET << "\n";
    std::cout << "Estimated delivery time: " << YELLOW << component->getDeliveryTime() << " days" << RESET << "\n";
    std::cout << "Time remaining: " << YELLOW << component->getTimeRemaining() << " days" << RESET << "\n";
    component->Operation();
}

// TESTS
void testIterator()
{
    std::cout << BOLD << BLUE << "\n=== Setting up Logistics Hierarchy ===" << RESET << std::endl;

    // Level 0
    ShipmentGroup *rootCargo = new ShipmentGroup(150.0, 5000.0, "Cape Town", 5);

    // Level 1
    ShipmentGroup *crateA = new ShipmentGroup(40.0, 1200.0, "Bloemfontein", 3);
    ShipmentGroup *crateB = new ShipmentGroup(60.0, 2500.0, "Cape Town", 4);

    // Level 2
    ShipmentGroup *palletB1 = new ShipmentGroup(30.0, 1500.0, "Cape Town", 2);

    // Level 2 & 3
    Package *pkg1 = new Package(10.0, 300.0, "Bloemfontein", 2);
    Package *pkg2 = new Package(15.0, 450.0, "Kimberley", 3);
    Package *pkg3 = new Package(5.0, 800.0, "Cape Town", 1);
    Package *pkg4 = new Package(8.0, 600.0, "Cape Town", 1);

    crateA->Add(pkg1);
    crateA->Add(pkg2);

    palletB1->Add(pkg3);
    palletB1->Add(pkg4);
    crateB->Add(palletB1);

    rootCargo->Add(crateA);
    rootCargo->Add(crateB);

    std::cout << "\n"
              << BOLD << BLUE << "=== Testing BFSIterator ===" << RESET << std::endl;

    Iterator *it = rootCargo->createBFSIterator();
    std::vector<ShippingComponent *> allNodes;
    for (it->first(); !it->isDone(); it->next())
    {
        allNodes.push_back(it->currentComponent());
    }

    if (!allNodes.empty())
    {
        std::queue<ShippingComponent *> q;
        q.push(rootCargo);

        int level = 0;
        while (!q.empty())
        {
            int levelSize = q.size();
            std::cout << "\n"
                      << MAGENTA << "--- Level " << level++ << " ---" << RESET << std::endl;

            for (int i = 0; i < levelSize; ++i)
            {
                ShippingComponent *node = q.front();
                q.pop();

                printShippingComponent(node);
                int childIdx = 0;
                ShippingComponent *child = node->GetChild(childIdx);
                while (child != nullptr)
                {
                    q.push(child);
                    childIdx++;
                    child = node->GetChild(childIdx);
                }
            }
        }
    }

    std::cout << "\n"
              << BOLD << BLUE << "=== Testing Traversal Reset (first) ===" << RESET << std::endl;
    it->first();
    if (!it->isDone() && it->currentComponent() != nullptr)
    {
        std::cout << GREEN << "Successfully reset to root: " << RESET;
        it->currentComponent()->Operation();
    }

    std::cout << "\n"
              << BOLD << BLUE << "=== Testing DestinationIterator (Filter: 'Cape Town') ===" << RESET << std::endl;
    Iterator *destIt = rootCargo->createDestinationIterator("Cape Town");

    int matchCount = 1;
    for (destIt->first(); !destIt->isDone(); destIt->next())
    {
        ShippingComponent *item = destIt->currentComponent();
        if (item != nullptr)
        {
            std::cout << "[" << matchCount++ << "] ";
            printShippingComponent(item);
        }
    }

    std::cout << "\n"
              << BOLD << BLUE << "=== Testing DestinationIterator (Filter: 'Kimberley') ===" << RESET << std::endl;
    Iterator *kimberleyIt = rootCargo->createDestinationIterator("Kimberley");

    matchCount = 1;
    for (kimberleyIt->first(); !kimberleyIt->isDone(); kimberleyIt->next())
    {
        ShippingComponent *item = kimberleyIt->currentComponent();
        if (item != nullptr)
        {
            std::cout << "[" << matchCount++ << "] ";
            printShippingComponent(item);
        }
    }

    std::cout << "\n"
              << BOLD << BLUE << "=== Testing CostFilterIterator (threshold: 1000) ===" << RESET << std::endl;
    Iterator *costIterator = rootCargo->createCostFilterIterator(1000);

    matchCount = 1;
    for (costIterator->first(); !costIterator->isDone(); costIterator->next())
    {
        ShippingComponent *item = costIterator->currentComponent();
        if (item != nullptr)
        {
            std::cout << "[" << matchCount++ << "] ";
            printShippingComponent(item);
        }
    }

    // Clean up
    delete destIt;
    delete kimberleyIt;
    delete costIterator;
    delete it;
    delete rootCargo;

    std::cout << "\n"
              << GREEN << "Iterator memory cleaned up safely." << RESET << std::endl;
}

void testCompositeDecorator()
{
    std::cout << "\n"
              << BOLD << BLUE << "=== Composite workflow ===" << RESET << "\n";

    ShipmentGroup *warehouse = new ShipmentGroup(150.0, 5000.0, "Cape Town", 5);
    ShipmentGroup *regional = new ShipmentGroup(80.0, 2200.0, "Bloemfontein", 3);
    ShipmentGroup *coldChain = new ShipmentGroup(90.0, 2600.0, "Johannesburg", 4);

    Package *basicBox = new Package(10.0, 400.0, "Kimberley", 2);
    ShippingComponent *fragileBox = new Fragile(new Package(6.0, 350.0, "Cape Town", 2));
    ShippingComponent *hazardBox = new Hazardous(new Package(12.0, 700.0, "Durban", 3));
    ShippingComponent *coldFragileBox = new Refridgerated(new Fragile(new Package(9.0, 560.0, "Bloemfontein", 3)));

    regional->Add(basicBox);
    regional->Add(fragileBox);
    coldChain->Add(hazardBox);
    coldChain->Add(coldFragileBox);

    warehouse->Add(regional);
    warehouse->Add(coldChain);

    printComponentInfo("Warehouse summary", warehouse);
    printComponentInfo("Regional shipment summary", regional);
    printComponentInfo("Cold chain summary", coldChain);

    std::cout << "\nWarehouse child count before removal: " << (warehouse->GetChild(0) != nullptr) + (warehouse->GetChild(1) != nullptr) << "\n";
    std::cout << "Regional first child destination: " << CYAN << regional->GetChild(0)->getDestination() << RESET << "\n";
    std::cout << "Cold chain second child destination: " << CYAN << coldChain->GetChild(1)->getDestination() << RESET << "\n";

    std::cout << "\n"
              << BOLD << "--- Advancing time through the structure ---" << RESET << "\n";
    warehouse->advanceDay();
    std::cout << "Warehouse time remaining after one day: " << YELLOW << warehouse->getTimeRemaining() << " days" << RESET << "\n";

    std::cout << "\n"
              << BOLD << "--- Removing a branch from the warehouse ---" << RESET << "\n";
    warehouse->Remove(regional);
    std::cout << "Warehouse child count after removal: " << (warehouse->GetChild(0) != nullptr) + (warehouse->GetChild(1) != nullptr) << "\n";

    delete warehouse;
    delete regional; // memory leak!! fixed
}

void testState()
{
    std::cout << "\n"
              << BOLD << BLUE << "=== State workflow ===" << RESET << "\n";

    Package parcel(5.5, 260.0, "Pretoria", 2);
    PackageJourney journey(&parcel);

    std::cout << "Initial status: " << journey.status() << "\n";
    journey.showStatus();

    std::cout << "\n"
              << MAGENTA << "Dispatch package" << RESET << "\n";
    journey.dispatch();
    journey.showStatus();

    std::cout << "\n"
              << RED << "Delay package" << RESET << "\n";
    journey.delay();
    journey.showStatus();

    std::cout << "\n"
              << YELLOW << "Resume package" << RESET << "\n";
    journey.resume();
    journey.showStatus();

    std::cout << "\n"
              << GREEN << "Deliver package" << RESET << "\n";
    journey.deliver();
    journey.showStatus();

    Package urgentParcel(3.0, 180.0, "Polokwane", 1);
    PackageJourney urgentJourney(&urgentParcel);

    urgentJourney.dispatch();
    urgentJourney.advanceDay();
    urgentJourney.showStatus();
    std::cout << "Urgent parcel due today? " << (urgentJourney.isDeliveryDue() ? GREEN + "Yes" : RED + "No") << RESET << "\n";
}

// --- Main Menu ---
int main()
{
    int choice = 0;
    while (choice != 4)
    {
        std::cout << "\n"
                  << BOLD << CYAN << "========================================" << RESET << "\n";
        std::cout << BOLD << CYAN << "       OCA Transport System Menu        " << RESET << "\n";
        std::cout << BOLD << CYAN << "========================================" << RESET << "\n";
        std::cout << "1. Run Iterator Tests (BFS, Destination, Cost)\n";
        std::cout << "2. Run Composite and Decorator tests\n";
        std::cout << "3. Run State Tests\n";
        std::cout << "4. Exit\n";
        std::cout << BOLD << "Select an option: " << RESET;

        std::cin >> choice;

        // Clear the newline character left in the buffer by std::cin
        std::cin.ignore(10000, '\n');

        switch (choice)
        {
        case 1:
            testIterator();
            goBackToMenu();
            break;
        case 2:
            testCompositeDecorator();
            goBackToMenu();
            break;
        case 3:
            testState();
            goBackToMenu();
            break;
        case 4:
            std::cout << GREEN << "\nExiting OCA Transport system. Goodbye!\n"
                      << RESET;
            break;
        default:
            std::cout << RED << "\nInvalid choice. Please enter a number between 1 and 4.\n"
                      << RESET;
            goBackToMenu();
        }
    }

    return 0;
}