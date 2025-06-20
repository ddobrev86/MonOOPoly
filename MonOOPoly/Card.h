#pragma once
#include "Player.h"
#include "SharedPtr.hpp"

class Card
{
public:
	virtual void printCardInfo() const = 0;
	virtual bool applyEffect(SharedPtr<Player>& player) const = 0;
};

