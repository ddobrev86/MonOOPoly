#pragma once

namespace MortgageConstants
{
	static const double COTTAGE_RENT_INCREASE = 0.15;
	static const double CASTLE_RENT_INCREASE = 0.5;
}

class Mortgage
{
protected:
	unsigned price;
	double rentIncrease = 0;
public:
	Mortgage(unsigned price);

	double getRentIncrease() const;
};

