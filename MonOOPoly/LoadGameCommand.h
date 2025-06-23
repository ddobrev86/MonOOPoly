#pragma once
#include "Command.h"

class LoadGameCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

