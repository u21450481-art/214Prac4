#ifndef _ITERATOR_H
#define _ITERATOR_H

class ShippingComponent;
class Iterator
{
    // friend of aggregate
public:
    virtual ~Iterator() = default;
    virtual void first() = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
    virtual ShippingComponent *currentComponent() const = 0;
};

#endif