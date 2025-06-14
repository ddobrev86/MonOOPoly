#pragma once
#include "MyString.h"
#include "BuildCommand.h"
#include "ThrowDiceCommand.h"
#include "BuyMortgageCommand.h"

class GameCommandFactory
{
public:
	static Command* createCommand(const MyString& command);
};

