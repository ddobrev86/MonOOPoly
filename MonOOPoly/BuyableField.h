#pragma once
#include "Field.h"
#include "MortgageManager.h"

class BuyableField : public Field
{
protected:
	MyString name;
	SharedPtr<Player> owner;
	unsigned price;
	unsigned rent;
public:
	BuyableField(const MyString& name, unsigned price, unsigned rent);

	virtual unsigned calculateTotalRent() const = 0;
	virtual BuyableField* clone() const = 0;

	unsigned sellPriceToBank() const;
	unsigned sellPriceToPlayer() const;
	virtual void sell();
	virtual void sellTo(const SharedPtr<Player>& newOwner);

	virtual void setUpMortgages(const SharedPtr<Mortgage>& castle,
		const SharedPtr<Mortgage>& cottage) = 0;
	virtual void buildMortgage(const MyString& mortgageType) = 0;
	virtual bool canBuyMortgages() const = 0;

	virtual void buy(SharedPtr<Player>& player);
	bool action(SharedPtr<Player>& player) override;

	bool belongsToPlayer(const SharedPtr<Player>& player) const;
	bool isFree() const;

	void printLandingMessage() const override;
	void printFieldInfo() const override;

	bool compareName(const MyString& name) const;

	const MyString& getName() const;
	SharedPtr<Player>& getOwner();

	void printUpForSaleMessage() const;
};

