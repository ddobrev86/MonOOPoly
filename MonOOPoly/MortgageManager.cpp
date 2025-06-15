#include "MortgageManager.h"

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
	const SharedPtr<Player>& owner, unsigned rent)
{
	unsigned totalOwed = getTotalRent(rent);
	if (owner->canAfford(totalOwed))
	{
		if (mortgageType == "cottage")
		{
			mortgages.push_back(cottage);
			return;
		}
		else if (mortgageType == "castle")
		{
			mortgages.push_back(castle);
			return;
		}

		throw std::invalid_argument("Invalid mortgage type");
	}

	throw std::runtime_error("You can't afford to build this property");
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
