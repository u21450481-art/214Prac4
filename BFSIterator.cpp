#include "BFSIterator.h"
#include "ShippingComponent.h"

BFSIterator::BFSIterator(ShippingComponent *rootComponent)
{
    root = rootComponent;
    current = nullptr;

    first(); // immediately add root to queue
}

void BFSIterator::first()
{
    // empty the queue
    while (!traverseQueue.empty())
    {
        traverseQueue.pop();
    }

    // place root at front
    if (root != nullptr)
    {
        traverseQueue.push(root);
        current = root;
    }
    else
    {
        current = nullptr; // the tree is empty
    }
}

bool BFSIterator::isDone() const
{
    // queue has no more nodes to be inspected
    return traverseQueue.empty();
}

void BFSIterator::next()
{
    if (isDone())
    {
        return; // queue is done
    }

    // get and pop node at the front
    ShippingComponent *visited = traverseQueue.front();
    traverseQueue.pop();

    // use getchild until its null, so all children is added
    int index = 0;

    ShippingComponent *child = visited->GetChild(index);

    while (child != nullptr)
    {
        traverseQueue.push(child);
        index++;
        child = visited->GetChild(index);
    }

    // set current to next node in the line

    if (!isDone())
    {
        current = traverseQueue.front();
    }
    else
    {
        current = nullptr;
    }
}

ShippingComponent *BFSIterator::currentComponent() const
{
    return current;
}