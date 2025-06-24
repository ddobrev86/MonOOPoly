#pragma once
#include "MyString.h"
#include "Command.h"

class BuildCommandFactory
{
public:
	static Command* createCommand(const MyString& command, MyVector<SharedPtr<FieldFamily>>& validFamilies);
};

