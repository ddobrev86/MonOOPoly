#pragma once
#include "SpecialField.h"
#include "MyDictionary.hpp"

//removes <times someone has landed on the field> * 5 % of the balance
class Facility : public SpecialField
{
public:
	Facility(const MyString& name, unsigned price);

	unsigned calculateTotalRent() const override;
	BuyableField* clone() const override;

	bool action(SharedPtr<Player>& player) override;
};

