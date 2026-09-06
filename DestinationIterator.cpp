#include "DestinationIterator.h"
#include "ShippingComponent.h"

DestinationIterator::DestinationIterator(ShippingComponent *rootComponent, const std::string &destination)
    : root(rootComponent), targetDestination(destination), currentIndex(0)
{
    first();
}

void DestinationIterator::collectMatches(ShippingComponent *comp)
{
    if (comp == nullptr)
        return;

    if (comp->getDestination() == targetDestination)
    {
        matchingItems.push_back(comp);
    }

    int index = 0;
    ShippingComponent *child = comp->GetChild(index);
    while (child != nullptr)
    {
        collectMatches(child);
        index++;
        child = comp->GetChild(index);
    }
}

void DestinationIterator::first()
{
    matchingItems.clear();
    currentIndex = 0;
    if (root != nullptr)
    {
        collectMatches(root);
    }
}

void DestinationIterator::next()
{
    if (!isDone())
    {
        currentIndex++;
    }
}

bool DestinationIterator::isDone() const
{
    return currentIndex >= matchingItems.size();
}

ShippingComponent *DestinationIterator::currentComponent() const
{
    if (isDone())
        return nullptr;
    return matchingItems[currentIndex];
}