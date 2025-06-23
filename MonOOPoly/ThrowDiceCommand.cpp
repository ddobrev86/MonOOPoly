#include "ThrowDiceCommand.h"

void ThrowDiceCommand::execute(Monopoly* monopoly)
{
	monopoly->actPlayerThrowDiceCommand();
}

Command* ThrowDiceCommand::clone() const
{
	return new ThrowDiceCommand(*this);
}
