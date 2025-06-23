#pragma once
#include "Command.h"

class PrintOwnershipMapCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

