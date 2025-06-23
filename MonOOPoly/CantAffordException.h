#pragma once
#include <stdexcept>
#include "MyString.h"

class CantAffordException : std::exception
{
private:
	MyString message;
public:
	CantAffordException(const char* msg);
	const char* what() const override;
};

