#pragma once
#include "Command.h"

class TradeWithBankCommand : public Command
{
public:
	void execute(Monopoly* monopoly) const override;
	Command* clone() const override;
};

