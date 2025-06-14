#pragma once
#include "CornerField.h"

class GoToJail : public CornerField
{
public:
	GoToJail();

	void printLandingMessage() const override;
	void printFieldInfo() const override;
	bool action(SharedPtr<Player>& player) override;
};

