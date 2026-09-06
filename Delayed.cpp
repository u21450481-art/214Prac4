#include "Delayed.h"

#include "Delivered.h"
#include "OnRoute.h"
#include "PackageJourney.h"

std::string Delayed::name() const 
{
    return "Delayed";
}

void Delayed::resume(PackageJourney& journey) 
{
    journey.changeState(new OnRoute());
}

void Delayed::deliver(PackageJourney& journey) 
{
    journey.changeState(new Delivered());
}
