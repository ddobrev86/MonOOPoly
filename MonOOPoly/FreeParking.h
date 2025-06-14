#pragma once
#include "CornerField.h"

class FreeParking : public CornerField
{
public:
	FreeParking();

	void printLandingMessage() const override;
	void printFieldInfo() const override;
	bool action(SharedPtr<Player>& player) override;
};

