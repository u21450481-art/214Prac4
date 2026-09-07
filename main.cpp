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

void printShippingComponent(ShippingComponent *node)
{
    std::cout << "  * " << node->getDestination()
              << " | " << node->getWeight() << " kg"
              << " | Cost: R" << node->getCost()
              << " | Est: " << node->getDeliveryTime() << " days"
              << std::endl;
}

void printComponentInfo(const std::string &label, ShippingComponent *component)
{
    std::cout << "\n=== " << label << " ===\n";
    std::cout << "Destination: " << component->getDestination() << "\n";
    std::cout << "Weight: " << component->getWeight() << " kg\n";
    std::cout << "Cost: R" << component->getCost() << "\n";
    std::cout << "Estimated delivery time: " << component->getDeliveryTime() << " days\n";
    std::cout << "Time remaining: " << component->getTimeRemaining() << " days\n";
    component->Operation();
}

void runCompositeWorkflow()
{
    std::cout << "\n=== Composite workflow ===\n";

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
    std::cout << "Regional first child destination: " << regional->GetChild(0)->getDestination() << "\n";
    std::cout << "Cold chain second child destination: " << coldChain->GetChild(1)->getDestination() << "\n";

    std::cout << "\n--- Advancing time through the structure ---\n";
    warehouse->advanceDay();
    std::cout << "Warehouse time remaining after one day: " << warehouse->getTimeRemaining() << " days\n";

    std::cout << "\n--- Removing a branch from the warehouse ---\n";
    warehouse->Remove(regional);
    std::cout << "Warehouse child count after removal: " << (warehouse->GetChild(0) != nullptr) + (warehouse->GetChild(1) != nullptr) << "\n";

    delete warehouse;
}

void runStateWorkflow()
{
    std::cout << "\n=== State workflow ===\n";

    Package parcel(5.5, 260.0, "Pretoria", 2);
    PackageJourney journey(&parcel);

    std::cout << "Initial status: " << journey.status() << "\n";
    journey.showStatus();

    std::cout << "\nDispatch package\n";
    journey.dispatch();
    journey.showStatus();

    std::cout << "\nDelay package\n";
    journey.delay();
    journey.showStatus();

    std::cout << "\nResume package\n";
    journey.resume();
    journey.showStatus();

    std::cout << "\nDeliver package\n";
    journey.deliver();
    journey.showStatus();

    Package urgentParcel(3.0, 180.0, "Polokwane", 1);
    PackageJourney urgentJourney(&urgentParcel);

    urgentJourney.dispatch();
    urgentJourney.advanceDay();
    urgentJourney.showStatus();
    std::cout << "Urgent parcel due today? " << (urgentJourney.isDeliveryDue() ? "Yes" : "No") << "\n";
}

int main()
{
    std::cout << "=== Setting up Logistics Hierarchy ===" << std::endl;

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

    std::cout << "\n=== Testing BFSIterator ===" << std::endl;

    // Traverse and collect items using your unmodified BFSIterator
    Iterator *it = rootCargo->createBFSIterator();
    std::vector<ShippingComponent *> allNodes;
    for (it->first(); !it->isDone(); it->next())
    {
        allNodes.push_back(it->currentComponent());
    }

    // Reconstruct the level groupings from the root down
    if (!allNodes.empty())
    {
        std::queue<ShippingComponent *> q;
        q.push(rootCargo);

        int level = 0;
        while (!q.empty())
        {
            int levelSize = q.size();
            std::cout << "\n--- Level " << level++ << " ---" << std::endl;

            for (int i = 0; i < levelSize; ++i)
            {
                ShippingComponent *node = q.front();
                q.pop();

                printShippingComponent(node);
                // Enqueue immediate children for the next level
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

    std::cout << "\n=== Testing Traversal Reset (first) ===" << std::endl;
    it->first();
    if (!it->isDone() && it->currentComponent() != nullptr)
    {
        std::cout << "Successfully reset to root: ";
        it->currentComponent()->Operation();
    }

    std::cout << "\n=== Testing DestinationIterator (Filter: 'Cape Town') ===" << std::endl;
    // Instantiate via aggregate factory method or direct constructor
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

    std::cout << "\n=== Testing DestinationIterator (Filter: 'Kimberley') ===" << std::endl;
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

    std::cout << "\n=== Testing CostFilterIterator (threshold:1000) ===" << std::endl;
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

    delete it; // Delete the iterator first
    delete rootCargo;

    std::cout << "\nMemory cleaned up safely." << std::endl;



    std::cout << "\n=== Workflow and Stateflow scenario begins ===\n";

    runCompositeWorkflow();
    runStateWorkflow();

    std::cout << "\n=== Workflow and Stateflow scenario complete ===\n";


    return 0;
}