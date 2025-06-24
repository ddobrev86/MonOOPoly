#pragma once
#include <stdexcept>

class GiveUpException : std::exception
{
public:
	const char* what() const override;
};

