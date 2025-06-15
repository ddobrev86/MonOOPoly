#pragma once
#include "MyString.h"
#include "BuildCommand.h"
#include "ThrowDiceCommand.h"
#include "BuyMortgageCommand.h"

class GameCommandFactory
{
private:
	static bool shouldBuild;
public:
	static Command* createCommand(const MyString& command);
};

