#include "BuyMortgageCommand.h"

BuyMortgageCommand::BuyMortgageCommand(bool& shouldBuild) : shouldBuild(shouldBuild)
{}

void BuyMortgageCommand::execute(Monopoly* monopoly)
{
	monopoly->actBuyMortgageCommand();
	shouldBuild = true;
}

Command* BuyMortgageCommand::clone() const
{
	return new BuyMortgageCommand(*this);
}
