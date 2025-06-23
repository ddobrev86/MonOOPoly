#pragma once
#include "Command.h"

class AddPaymentCardCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

