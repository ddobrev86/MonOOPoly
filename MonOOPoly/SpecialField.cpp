#include "SpecialField.h"

SpecialField::SpecialField(const MyString& name, 
    unsigned price, unsigned rent) : BuyableField(name, price, rent)
{}

void SpecialField::setUpMortgages(const SharedPtr<Mortgage>& castle, const SharedPtr<Mortgage>& cottage)
{}

bool SpecialField::canBuyMortgages() const
{
    return false;
}

void SpecialField::buildMortgage(const MyString& mortgageType)
{}

