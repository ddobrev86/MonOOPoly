#include "GroupPaymentCard.h"
#include "PendingPayment.h"
#include "Bank.h"

GroupPaymentCard::GroupPaymentCard(int balanceChange, MyVector<SharedPtr<Player>>& players) : players(players)
{
    this->balanceChange = balanceChange;
    //this->players = players;
}

void GroupPaymentCard::printCardInfo() const
{
	std::cout << "You drew a Group Payment Card\n";
	if (balanceChange < 0)
		std::cout << "You have to give " << -balanceChange << " to each player" << '\n';
	else
	{
		std::cout << "You get " << balanceChange << " from each player" << '\n';
		std::cout << "\n*Note: Players that don't have enough give you all their remaining balance*\n";
	}


	system("pause");
	system("cls");
}

bool GroupPaymentCard::applyEffect(SharedPtr<Player>& player) const
{
	int totalChange = balanceChange * (players.getSize() - 1);

	if (balanceChange < 0)
	{
		PendingPayment::clear();
		PendingPayment::setPayer(player);

		Bank::getFrom(player, -totalChange, true);

		for (size_t i = 0; i < players.getSize(); i++)
		{
			if (players[i] == player)
				continue;

			SharedPtr<Player> current = players[i];
			Bank::giveTo(current, -balanceChange);
		}
	}
	else
	{
		unsigned amountToGive;
		for (size_t i = 0; i < players.getSize(); i++)
		{
			if (players[i] == player)
				continue;

			SharedPtr<Player> current = players[i];

			Bank::getEverythingFrom(current, balanceChange, amountToGive);
			Bank::giveTo(player, amountToGive);
		}

	}

    return true;
}
