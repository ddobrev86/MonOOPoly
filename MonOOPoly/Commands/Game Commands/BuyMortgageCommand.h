#pragma once
#include "Command.h"

class BuyMortgageCommand : public Command
{
private:
	bool& shouldBuild;
public:
	BuyMortgageCommand(bool& shouldBuild);

	void execute(Monopoly* monopoly) const override;
	Command* clone() const override;
};

