#pragma once
#include "Command.h"

class GameElementsCommandFactory
{
public:
	static Command* createCommand(const MyString& command);
};

