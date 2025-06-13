#pragma once
#include "MortgageManager.h"
#include "BuyableField.h"
#include "MyDictionary.hpp"

class Station : public BuyableField
{
private:
	static MyDictionary<SharedPtr<Player>, size_t> ownersipMap;

public:

	Station(const MyString& name, unsigned price, unsigned rent);

	void buy(SharedPtr<Player>& player) override;

	size_t calculateTotalRent() const override;
	BuyableField* clone() const override;

	void setUpMortgages(const SharedPtr<Mortgage>& castle,
		const SharedPtr<Mortgage>& cottage) override;
	bool canBuyMortgages() const override;

	bool action(SharedPtr<Player>& player) override;
};



