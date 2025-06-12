#pragma once
#include "MortgageManager.h"
#include "BuyableField.h"

class Property : public BuyableField
{
private:
	UniquePtr<MortgageManager> mortgageManager;

public:
	Property(const MyString& name, unsigned price, unsigned rent);
	void buyMortgage();
	size_t calculateTotalRent() const override;

	/*bool belongsToPlayer(const SharedPtr<Player>& player);
	bool isFree() const;*/
	//void printFieldInfo() const override;
	//void action(SharedPtr<Player>& player) override;
	//void buy(SharedPtr<Player>& player);
	
};

