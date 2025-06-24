#pragma once
#include "Command.h"

class AddGroupPaymentCardCommand : public Command
{
public:
	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

