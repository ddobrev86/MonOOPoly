#pragma once
#include "Command.h"

class AddPlayerCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

