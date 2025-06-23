#pragma once
#include "Command.h"

class ManualGameCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

