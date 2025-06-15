#pragma once
#include "SharedPtr.hpp"
#include "Player.h"

class Field 
{
public:
	virtual void printLandingMessage() const = 0;
	virtual void printFieldInfo() const = 0;
	virtual bool action(SharedPtr<Player>& player) = 0;
	//virtual Field* clone() const = 0;
};

