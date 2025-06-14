#pragma once
#include "Command.h"

class BuyMortgageCommand : public Command
{
public:
	void execute(Monopoly* monopoly) const override;
	Command* clone() const override;
};

