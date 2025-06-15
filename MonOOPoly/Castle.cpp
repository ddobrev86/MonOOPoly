#include "Castle.h"

Castle::Castle(unsigned price) : Mortgage(price)
{
	rentIncrease = MortgageConstants::CASTLE_RENT_INCREASE;
}
