#pragma once
#include "utilities.h"

class Mortgage
{
protected:
	unsigned price;
	double rentIncrease = 0;
public:
	Mortgage(unsigned price);

	double getRentIncrease() const;
};

