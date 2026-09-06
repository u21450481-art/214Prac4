#ifndef PACKAGEJOURNEY_H
#define PACKAGEJOURNEY_H

#include <string>

#include "PackageState.h"

class ShippingComponent;
class NotDelivered;
class OnRoute;
class Delayed;
class Delivered;

class PackageJourney { //Context (State Deisgn Pattern)

    private:
        ShippingComponent* package;
        PackageState* state; //current state of the package

        void changeState(PackageState* nextState);

        friend class NotDelivered;
        friend class OnRoute;
        friend class Delayed;
        friend class Delivered;

    public:
        explicit PackageJourney(ShippingComponent* package);
        ~PackageJourney();

        // State transitions
        void dispatch();
        void delay();
        void resume();
        void deliver();

        //used as guards for state transitions
        void advanceDay();
        void checkDeliveryTime();

        std::string status() const;
        void showStatus() const;
        bool isDeliveryDue() const;
        ShippingComponent* getPackage() const;
};

#endif
