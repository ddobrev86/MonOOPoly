#pragma once
#include "SharedPtr.hpp"
#include "MyVector.hpp"
#include "MyString.h"
#include "Player.h"
#include "Mortgage.h"

class MortgageManager
{
private:
	static const unsigned MIN_COTTAGES_FOR_CASTLE = 3;

	MyVector<SharedPtr<Mortgage>> mortgages;

	SharedPtr<Mortgage> castle;
	SharedPtr<Mortgage> cottage;

public:
	MortgageManager(const SharedPtr<Mortgage>& castle,
		const SharedPtr<Mortgage>& cottage);

	void setUpMortgages(const SharedPtr<Mortgage>& castle,
		const SharedPtr<Mortgage>& cottage);

	void buyMortgage(const SharedPtr<Mortgage>& mortgage);
	void buildMortgage(const MyString& mortgageType,
		SharedPtr<Player>& owner, unsigned rent);

	bool canBuyCastle() const;

	unsigned getTotalRent(unsigned originalRent) const;
};

