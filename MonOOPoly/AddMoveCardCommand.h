#pragma once
#include "Command.h"

class AddMoveCardCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

