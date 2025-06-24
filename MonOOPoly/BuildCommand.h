#pragma once
#include "Command.h"

class BuildCommand : public Command
{
private:
	MyVector<SharedPtr<FieldFamily>>& validFamilies;
public:
	BuildCommand(MyVector<SharedPtr<FieldFamily>>& validFamilies);

	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

