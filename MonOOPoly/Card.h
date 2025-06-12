#pragma once
#include "Player.h"
#include "SharedPtr.hpp"

class Card
{
public:
	virtual void applyEffect(SharedPtr<Player>& player) const = 0;
};

