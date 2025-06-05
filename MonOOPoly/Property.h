#pragma once
#include "Field.h"
#include "SharedPtr.hpp"

class Property : public Field
{
private:
	//SharedPtr<> owner;
	unsigned price;
	unsigned cottageCost;
	unsigned castleCost;
	unsigned rent;
public:
	Property(unsigned price, unsigned cottageCost,
		unsigned castleCost, unsigned rent);
};

