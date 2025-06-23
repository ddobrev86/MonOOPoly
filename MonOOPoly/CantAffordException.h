#pragma once
#include <stdexcept>
#include "MyString.h"

class CantAffordException : std::exception
{
private:
	MyString message;
	int neededAmount;

public:
	CantAffordException(const char* msg, int neededAmount);
	const char* what() const override;
	int getNeededAmount() const;
};

