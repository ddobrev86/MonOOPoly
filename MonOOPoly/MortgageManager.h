#pragma once
#include "SharedPtr.hpp"
#include "Mortgage.h"
#include "MyVector.hpp"

class MortgageManager
{
private:
	static const unsigned MIN_COTTAGES_FOR_CASTLE = 3;

	MyVector<SharedPtr<Mortgage>> mortgages;

public:
	void buyMortgage(const SharedPtr<Mortgage>& mortgage);

	bool canBuyCastle() const;

	unsigned getTotalRent(unsigned originalRent) const;
};

