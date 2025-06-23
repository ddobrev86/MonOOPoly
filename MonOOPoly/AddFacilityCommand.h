#pragma once
#include "Command.h"

class AddFacilityCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

