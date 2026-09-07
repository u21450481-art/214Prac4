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
    return 0;
}