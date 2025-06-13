#pragma once
#include "SpecialField.h"
#include "MyDictionary.hpp"

//the rent is based on the total amount of Stations a player owns
// + when someone, other than the owner, steps on this 
//field he moves 3 positions ahead
class Station : public SpecialField
{
private:
	static MyDictionary<SharedPtr<Player>, size_t> ownersipMap;

public:
	Station(const MyString& name, unsigned price, unsigned rent);

	void buy(SharedPtr<Player>& player) override;

	size_t calculateTotalRent() const override;
	BuyableField* clone() const override;

	bool action(SharedPtr<Player>& player) override;
};



