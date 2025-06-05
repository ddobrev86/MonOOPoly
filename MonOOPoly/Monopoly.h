#pragma once
#include "MyVector.hpp"
#include "Board.h"

class Monopoly
{
private:
	static Monopoly* instance;
	UniquePtr<Board> board;

	Monopoly();
};

