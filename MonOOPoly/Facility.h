#pragma once
#include "SpecialField.h"
#include "MyDictionary.hpp"

//after each stepping on the field, the rent increases by a 
// factor of the times someone has stepped on the field
class Facility : public SpecialField
{
private:
	mutable size_t multiplier;

public:
	Facility(const MyString& name, unsigned price, unsigned rent);

	size_t calculateTotalRent() const override;
	BuyableField* clone() const override;
};

