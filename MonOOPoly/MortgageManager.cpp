#include "MortgageManager.h"

void MortgageManager::buyMortgage(const SharedPtr<Mortgage>& mortgage)
{
	mortgages.push_back(mortgage);
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
