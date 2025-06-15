#pragma once
#include "Command.h"

class ThrowDiceCommand : public Command
{
public:
	void execute(Monopoly* monopoly) const override;
	Command* clone() const override;
};

