#include "MortgageManager.h"
#include "Bank.h"

MortgageManager::MortgageManager(const SharedPtr<Mortgage>& castle, 
	const SharedPtr<Mortgage>& cottage) : castle(castle), cottage(cottage)
{}

void MortgageManager::setUpMortgages(const SharedPtr<Mortgage>& castle, const SharedPtr<Mortgage>& cottage)
{
	this->castle = castle;
	this->cottage = cottage;
}

void MortgageManager::buyMortgage(const SharedPtr<Mortgage>& mortgage)
{
	mortgages.push_back(mortgage);
}

void MortgageManager::buildMortgage(const MyString& mortgageType, 
	SharedPtr<Player>& owner, unsigned rent)
{
	SharedPtr<Mortgage> mortgage;

	if (mortgageType == "cottage")
		mortgage = cottage;
	else if (mortgageType == "castle")
		mortgage = castle;
	else
		throw std::invalid_argument("Invalid mortgage type");

	Bank::getFrom(owner, mortgage->getPrice(), false);
	mortgages.push_back(mortgage);

	//throw std::runtime_error("You can't afford to build this mortgage");
}

bool MortgageManager::canBuyCastle() const
{
	return mortgages.getSize() >= MIN_COTTAGES_FOR_CASTLE;
}

unsigned MortgageManager::getTotalRent(unsigned originalRent) const
{
	unsigned result = originalRent;
	for (size_t i = 0; i < mortgages.getSize(); i++)
	{
		unsigned costIncrease = originalRent * (1 + mortgages[i]->getRentIncrease());
		result += costIncrease;
	}

	return result;
}
