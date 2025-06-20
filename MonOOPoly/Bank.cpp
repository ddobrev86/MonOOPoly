#include "Bank.h"

void Bank::giveInitialBalance(MyVector<SharedPtr<Player>>& players)
{
	for (size_t i = 0; i < players.getSize(); i++)
		players[i]->addToBalance(1500);
}

void Bank::getFrom(SharedPtr<Player>& player, unsigned sum)
{
	player->removeFromBalance(sum);
}

void Bank::giveTo(SharedPtr<Player>& player, unsigned sum)
{
	player->addToBalance(sum);
}

void Bank::goTroughStart(SharedPtr<Player>& player)
{
	giveTo(player, 200);
}

void Bank::goTroughStart(Player* player)
{
	player->addToBalance(200);
}
