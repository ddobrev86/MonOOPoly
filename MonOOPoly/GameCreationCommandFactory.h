#pragma once
#include "MyString.h"
#include "LoadGameCommand.h"
#include "DefualtGameCommand.h"
#include "ManualGameCommand.h"

class GameCreationCommandFactory
{
public:
	static Command* createCommand(const MyString& command, bool& isDefault);
};

