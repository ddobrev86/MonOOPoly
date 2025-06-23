#pragma once
#include "Command.h"

class AddPropertyFamilyCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

