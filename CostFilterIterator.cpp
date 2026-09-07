#include "CostFilterIterator.h"
#include "ShippingComponent.h"

CostFilterIterator::CostFilterIterator(ShippingComponent *rootComponent, double costThreshold)
    : root(rootComponent), threshold(costThreshold), currentIndex(0)
{
    first();
}

void CostFilterIterator::collectMatches(ShippingComponent *comp)
{
    if (comp == nullptr)
    {
        return;
    }

    // select components whose cost>threshold
    if (comp->getCost() > threshold)
    {
        matchingItems.push_back(comp);
    }

    // recursively collect
    int index = 0;
    ShippingComponent *child = comp->GetChild(index);
    while (child != nullptr)
    {
        collectMatches(child);
        index++;
        child = comp->GetChild(index);
    }
}

void CostFilterIterator::first()
{
    matchingItems.clear();
    currentIndex = 0;
    if (root != nullptr)
    {
        collectMatches(root);
    }
}

void CostFilterIterator::next()
{
    if (!isDone())
    {
        currentIndex++;
    }
}

bool CostFilterIterator::isDone() const
{
    return currentIndex >= matchingItems.size();
}

ShippingComponent *CostFilterIterator::currentComponent() const
{
    if (isDone())
    {
        return nullptr;
    }
    return matchingItems[currentIndex];
}