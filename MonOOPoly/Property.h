#pragma once
#include "Field.h"
#include "MortgageManager.h"
#include "MyString.h"

class Property : public Field
{
private:
	MyString name;
	SharedPtr<Player> owner;
	unsigned price;
	UniquePtr<MortgageManager> mortgageManager;
	unsigned rent;

public:
	Property(const MyString& name, unsigned price, unsigned rent);

	bool belongsToPlayer(const SharedPtr<Player>& player);
	bool isFree() const;

	void printFieldInfo() const override;
	void action(SharedPtr<Player>& player) override;

	void buy(SharedPtr<Player>& player);
	void buyMortgage();
};

