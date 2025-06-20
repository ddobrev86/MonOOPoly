#pragma once
#include "Player.h"
#include "SharedPtr.hpp"

class Card
{
public:
	virtual void printCardInfo() const = 0;
	virtual void applyEffect(SharedPtr<Player>& player) const = 0;
};

