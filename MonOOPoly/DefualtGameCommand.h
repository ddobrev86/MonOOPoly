#pragma once
#include "Command.h"

class DefualtGameCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

