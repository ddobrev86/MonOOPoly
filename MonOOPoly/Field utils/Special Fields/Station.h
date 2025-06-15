#pragma once
#include "SpecialField.h"
#include "MyDictionary.hpp"

//after each stepping on the field, the rent increases by a 
//factor of the times someone has stepped on the field,
//multiplied by the number of stations owned by the same player
class Station : public SpecialField
{
private:
	static MyDictionary<SharedPtr<Player>, size_t> ownersipMap;

public:
	Station(const MyString& name, unsigned price, unsigned rent);

	void buy(SharedPtr<Player>& player) override;

	size_t calculateTotalRent() const override;
	BuyableField* clone() const override;
};



