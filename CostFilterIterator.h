#ifndef COST_FILTER_ITERATOR_H
#define COST_FILTER_ITERATOR_H

#include "Iterator.h"
#include <vector>
#include <cstddef>

class ShippingComponent;

class CostFilterIterator : public Iterator
{
private:
    ShippingComponent *root;
    double threshold;
    std::vector<ShippingComponent *> matchingItems;
    std::size_t currentIndex;

    void collectMatches(ShippingComponent *comp);

public:
    CostFilterIterator(ShippingComponent *rootComponent, double costThreshold);
    ~CostFilterIterator() override = default;

    void first() override;
    void next() override;
    bool isDone() const override;
    ShippingComponent *currentComponent() const override;
};

#endif