#include "Bank.h"
#include "CantAffordException.h"

void Bank::giveInitialBalance(MyVector<SharedPtr<Player>>& players)
{
	for (size_t i = 0; i < players.getSize(); i++)
		players[i]->addToBalance(1500);
}

void Bank::getFrom(SharedPtr<Player>& player, unsigned sum, bool isImportant)
{
	if (isImportant)
	{
		try
		{
			player->removeFromBalance(sum);
		}
		catch (const std::exception& excp)
		{
			std::cout << excp.what();
			throw new CantAffordException("You have to trade");
		}
	}
	else
	{
		player->removeFromBalance(sum);
	}
}

void Bank::giveTo(SharedPtr<Player>& player, unsigned sum)
{
	player->addToBalance(sum);
}

void Bank::landOnStart(SharedPtr<Player>& player)
{
	giveTo(player, 200);
}

void Bank::landOnStart(Player* player)
{
	player->addToBalance(200);
}

void Bank::goTroughStart(SharedPtr<Player>& player)
{
	std::cout << "You have gone over Start\n";
	std::cout << "You receive $200\n";
	landOnStart(player);
}

void Bank::goTroughStart(Player* player)
{
	std::cout << "You have gone over Start\n";
	std::cout << "You receive $200\n\n";
	landOnStart(player);
}
