#include "Mortgage.h"

Mortgage::Mortgage(unsigned price)
{
	this->price = price;
}

double Mortgage::getRentIncrease() const
{
	return rentIncrease;
}

unsigned Mortgage::getPrice() const
{
	return price;
}
