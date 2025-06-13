#include "Facility.h"

Facility::Facility(const MyString& name, 
    unsigned price, unsigned rent) : SpecialField(name, price, rent)
{
    multiplier = 1;
}

size_t Facility::calculateTotalRent() const
{   
    return rent * (multiplier++);
}

BuyableField* Facility::clone() const
{
    return new Facility(*this);
}
