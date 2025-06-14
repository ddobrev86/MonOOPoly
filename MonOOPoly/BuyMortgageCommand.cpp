#include "BuyMortgageCommand.h"

void BuyMortgageCommand::execute(Monopoly* monopoly) const
{
	monopoly->actBuyMortgageCommand();
}

Command* BuyMortgageCommand::clone() const
{
	return new BuyMortgageCommand(*this);
}
