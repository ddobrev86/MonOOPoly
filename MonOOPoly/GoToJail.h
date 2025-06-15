#pragma once
#include "CornerField.h"

class GoToJail : public CornerField
{
private:
	size_t jailPosition;
public:
	GoToJail(size_t jailPosition);

	void printLandingMessage() const override;
	void printFieldInfo() const override;
	bool action(SharedPtr<Player>& player) override;
};

