#ifndef PACKAGESTATE_H
#define PACKAGESTATE_H

#include <string>

class PackageJourney;

class PackageState { //State

    public:
        virtual ~PackageState();

        virtual std::string name() const = 0;
        virtual void dispatch(PackageJourney& journey);
        virtual void delay(PackageJourney& journey);
        virtual void resume(PackageJourney& journey);
        virtual void deliver(PackageJourney& journey);
        virtual void checkDeliveryTime(PackageJourney& journey);
};

#endif
