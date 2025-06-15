#pragma once
#include "MortgageManager.h"
#include "BuyableField.h"

class Property : public BuyableField
{
private:
	SharedPtr<MortgageManager> mortgageManager;

public:
	Property(const MyString& name, unsigned price, unsigned rent);
	void buildMortgage(const MyString& mortgageType) override;

	unsigned calculateTotalRent() const override;
	BuyableField* clone() const override;

	void setUpMortgages(const SharedPtr<Mortgage>& castle,
		const SharedPtr<Mortgage>& cottage) override;
	bool canBuyMortgages() const override;

	/*bool belongsToPlayer(const SharedPtr<Player>& player);
	bool isFree() const;*/
	//void printFieldInfo() const override;
	//void action(SharedPtr<Player>& player) override;
	//void buy(SharedPtr<Player>& player);
	
};

