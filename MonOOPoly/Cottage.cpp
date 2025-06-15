#include "Cottage.h"

Cottage::Cottage(unsigned price) : Mortgage(price)
{
	rentIncrease = MortgageConstants::COTTAGE_RENT_INCREASE;
}
