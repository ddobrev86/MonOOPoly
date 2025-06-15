#pragma once
#include "Command.h"

class AddPlayerCommand : public Command
{
public:
	void execute(Monopoly* monopoly) const override;
	Command* clone() const override;
};

