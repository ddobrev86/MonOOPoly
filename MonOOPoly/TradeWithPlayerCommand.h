#pragma once
#include "Command.h"

class TradeWithPlayerCommand : public Command
{
public:
	void execute(Monopoly* monopoly) const override;
	Command* clone() const override;
};

