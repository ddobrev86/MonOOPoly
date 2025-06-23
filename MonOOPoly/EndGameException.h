#pragma once
#include <stdexcept>
#include "Player.h"
#include "SharedPtr.hpp"

class EndGameException : std::exception
{
private:
	SharedPtr<Player> winner;
public:
	EndGameException(const SharedPtr<Player>& winner);

	const char* what() const override;
};

