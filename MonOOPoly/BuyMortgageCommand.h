#pragma once
#include "Command.h"

class BuyMortgageCommand : public Command
{
public:
	BuyMortgageCommand();

	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

