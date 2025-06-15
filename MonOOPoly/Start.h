#pragma once
#include "CornerField.h"

class Start : public CornerField
{
public:
	Start();

	void printLandingMessage() const override;
	void printFieldInfo() const override;
	bool action(SharedPtr<Player>& player) override;
};

