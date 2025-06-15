#pragma once
#include "CornerField.h"

class Jail : public CornerField
{
public:
	Jail();

	void printLandingMessage() const override;
	void printFieldInfo() const override;
	bool action(SharedPtr<Player>& player) override;
};

