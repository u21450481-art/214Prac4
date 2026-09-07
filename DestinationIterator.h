#ifndef DESTINATION_ITERATOR_H
#define DESTINATION_ITERATOR_H

#include "Iterator.h"
#include <string>
#include <vector>

class ShippingComponent;

class DestinationIterator : public Iterator
{
private:
    ShippingComponent *root;
    std::string targetDestination;
    std::vector<ShippingComponent *> matchingItems;
    size_t currentIndex;

    void collectMatches(ShippingComponent *comp);

public:
    DestinationIterator(ShippingComponent *rootComponent, const std::string &destination);
    ~DestinationIterator() override = default;

    void first() override;
    void next() override;
    bool isDone() const override;
    ShippingComponent *currentComponent() const override;
};

#endif