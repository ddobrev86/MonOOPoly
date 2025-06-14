#pragma once
#include "Monopoly.h"
#include <iostream>
#include <stdexcept>

class Command
{
public:
	virtual void execute(Monopoly* monopoly) const = 0;
	virtual Command* clone() const = 0;
	virtual ~Command() = default;
};

