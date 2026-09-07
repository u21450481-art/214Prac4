#ifndef BFS_ITERATOR_H
#define BFS_ITERATOR_H

#include "Iterator.h"
#include <queue>

class ShippingComponent;

class BFSIterator : public Iterator
{
private:
    ShippingComponent *root;
    std::queue<ShippingComponent *> traverseQueue;
    ShippingComponent *current;

public:
    BFSIterator(ShippingComponent *rootComponent);
    ~BFSIterator() override = default; // queue manages its own destruction

    void first() override;
    void next() override;
    bool isDone() const override;
    ShippingComponent *currentComponent() const override;
};

#endif