#pragma once
#include "Command.h"

class AddPropertyCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};
