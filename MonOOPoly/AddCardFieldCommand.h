#pragma once
#include "Command.h"

class AddCardFieldCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

