#pragma once
#include "Command.h"

class BuildCommand : public Command
{
private:
	bool& shouldBuild;
public:
	BuildCommand(bool& shouldBuild);

	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

