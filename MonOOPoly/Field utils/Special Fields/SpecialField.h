#pragma once
#include "BuyableField.h"

class SpecialField : public BuyableField
{
protected:
	mutable size_t multiplier;

public:
	SpecialField(const MyString& name, unsigned price, unsigned rent);

	void setUpMortgages(const SharedPtr<Mortgage>& castle,
		const SharedPtr<Mortgage>& cottage) override;
	bool canBuyMortgages() const override;
	void buildMortgage(const MyString& mortgageType) override;
};

