#pragma once
#include "MyString.h"
#include "Command.h"

class GameCommandFactory
{
private:
	static bool shouldBuild;
public:
	static Command* createCommand(const MyString& command);
};

