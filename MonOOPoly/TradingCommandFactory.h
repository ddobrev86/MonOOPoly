#pragma once
#include "MyString.h"
#include "Command.h"

class TradingCommandFactory
{
public:
	static Command* createCommand(const MyString& command, 
		SharedPtr<BuyableField>& fieldToTrade, int& neededAmount);
};

