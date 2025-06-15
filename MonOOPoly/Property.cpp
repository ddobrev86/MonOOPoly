#include "Property.h"
#include "InputProcessor.h"

Property::Property(const MyString& name, unsigned price, unsigned rent) : BuyableField(name, price, rent)
{}

void Property::buildMortgage(const MyString & mortgageType)
{
	mortgageManager->buildMortgage(mortgageType, owner, rent);
}

size_t Property::calculateTotalRent() const
{
	return mortgageManager->getTotalRent(rent);
}

BuyableField* Property::clone() const
{
	return new Property(*this);
}

void Property::setUpMortgages(const SharedPtr<Mortgage>& castle, const SharedPtr<Mortgage>& cottage)
{
	mortgageManager = SharedPtr<MortgageManager>(new MortgageManager(castle, cottage));
}

bool Property::canBuyMortgages() const
{
	return true;
}
