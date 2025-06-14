#pragma once
#include "Command.h"

class BuildCommand : public Command
{
public:
	void execute(Monopoly* monopoly) const override;
	Command* clone() const override;
};

