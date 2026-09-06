#include "ShipmentGroup.h"
#include "BFSIterator.h"
#include "DestinationIterator.h"
#include "CostFilterIterator.h"
#include <iomanip>
#include <iostream>

ShipmentGroup::ShipmentGroup(double weight, double cost, const std::string &destination,
                             int deliveryTime)
    : ShippingComponent(weight, cost, destination, deliveryTime), children()
{
}

ShipmentGroup::~ShipmentGroup()
{
    for (unsigned int i = 0; i < this->children.size(); i++)
    {
        delete this->children[i];
    }
    this->children.clear();
}

void ShipmentGroup::Operation()
{
    std::cout << "ShipmentGroup -> " << getDestination()
              << " | " << this->children.size() << " item(s)"
              << " | " << std::fixed << std::setprecision(2) << getWeight() << " kg"
              << " | cost " << std::fixed << std::setprecision(2) << getCost()
              << " | " << getDeliveryTime() << " days"
              << std::endl;

    for (unsigned int i = 0; i < this->children.size(); i++)
    {
        this->children[i]->Operation();
    }
}

void ShipmentGroup::Add(ShippingComponent *c)
{
    if (c == NULL || c == this)
    {
        return;
    }
    this->children.push_back(c);
}

void ShipmentGroup::Remove(ShippingComponent *c)
{
    for (unsigned int i = 0; i < this->children.size(); i++)
    {
        if (this->children[i] == c)
        {
            this->children.erase(this->children.begin() + i);
            return;
        }
    }
}

ShippingComponent *ShipmentGroup::GetChild(int index)
{
    if (index < 0 || index >= (int)this->children.size())
    {
        return NULL;
    }
    return this->children[index];
}

double ShipmentGroup::getWeight() const
{
    double total = this->weight;
    for (unsigned int i = 0; i < this->children.size(); i++)
    {
        total += this->children[i]->getWeight();
    }
    return total;
}

double ShipmentGroup::getCost() const
{
    double total = this->cost;
    for (unsigned int i = 0; i < this->children.size(); i++)
    {
        total += this->children[i]->getCost();
    }
    return total;
}

/* The group arrives when its slowest child arrives, so this combines by max, not by sum. */
int ShipmentGroup::getDeliveryTime() const
{
    int slowest = 0;
    for (unsigned int i = 0; i < this->children.size(); i++)
    {
        int childTime = this->children[i]->getDeliveryTime();
        if (childTime > slowest)
        {
            slowest = childTime;
        }
    }
    return this->deliveryTime + slowest;
}

int ShipmentGroup::getTimeRemaining() const
{
    int slowest = 0;
    for (unsigned int i = 0; i < this->children.size(); i++)
    {
        int childTime = this->children[i]->getTimeRemaining();
        if (childTime > slowest)
        {
            slowest = childTime;
        }
    }
    return this->timeRemaining + slowest;
}

/*
 * Handling happens before transit, not at the same time: the group works off its
 * own countdown first and only then lets the children move. Decrementing both in
 * one call would take two days off the total for one day elapsed.
 */
void ShipmentGroup::advanceDay()
{
    if (this->timeRemaining > 0)
    {
        this->timeRemaining--;
        return;
    }

    for (unsigned int i = 0; i < this->children.size(); i++)
    {
        this->children[i]->advanceDay();
    }
}

// making concrete iterators
// In ShipmentGroup.cpp
Iterator *ShipmentGroup::createBFSIterator()
{
    return new BFSIterator(this);
}

Iterator *ShipmentGroup::createDestinationIterator(const std::string &dest)
{
    return new DestinationIterator(this, dest);
}

Iterator *ShipmentGroup::createCostFilterIterator(double threshold)
{
    return new CostFilterIterator(this, threshold);
}
