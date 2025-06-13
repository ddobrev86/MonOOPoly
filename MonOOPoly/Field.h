#pragma once
#include "SharedPtr.hpp"
#include "Player.h"

class Field 
{
public:
	virtual void printFieldInfo() const = 0;
	virtual void action(SharedPtr<Player>& player) = 0;
	//virtual Field* clone() const = 0;
};

