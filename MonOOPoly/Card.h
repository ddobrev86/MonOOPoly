#pragma once
#include "Player.h"

class Card
{
public:
	virtual void applyEffect(Player& player) const = 0;
};

