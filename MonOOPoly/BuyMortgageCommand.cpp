#include "BuyMortgageCommand.h"

BuyMortgageCommand::BuyMortgageCommand()
{}

void BuyMortgageCommand::execute(Monopoly* monopoly)
{
	monopoly->actBuyMortgageCommand();
}

Command* BuyMortgageCommand::clone() const
{
	return new BuyMortgageCommand(*this);
}
