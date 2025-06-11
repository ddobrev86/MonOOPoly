#pragma once
#include "Field.h"
#include "MortgageManager.h"

class Property : public Field
{
private:
	SharedPtr<Player> owner;
	unsigned price;
	UniquePtr<MortgageManager> mortgages;
	unsigned rent;

public:
	Property(unsigned price, unsigned rent);

	bool belongsToPlayer(const SharedPtr<Player>& player);
	bool isFree() const;

	void printFieldInfo() const override;
	void action(SharedPtr<Player>& player) override;

	void buy(SharedPtr<Player>& player);
	void buyMortgage();
};

