#pragma once
#include "SharedPtr.hpp"
#include "MyVector.hpp"
#include "Player.h"

class Bank
{
private:
	unsigned bankBalance = 20580;
public:
	static void giveInitialBalance(MyVector<SharedPtr<Player>>& players);

	static void getFrom(SharedPtr<Player>& player, unsigned sum);
	static void giveTo(SharedPtr<Player>& player, unsigned sum);

	static void landOnStart(SharedPtr<Player>& player);
	static void landOnStart(Player* player);

	static void goTroughStart(SharedPtr<Player>& player);
	static void goTroughStart(Player* player);
};

