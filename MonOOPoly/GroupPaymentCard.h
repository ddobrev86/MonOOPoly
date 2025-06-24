#pragma once
#include "Card.h"
#include "MyVector.hpp"
#include "SharedPtr.hpp"
#include "Player.h"

class GroupPaymentCard : public Card
{
private:
	int balanceChange;
	MyVector<SharedPtr<Player>>& players;
public:
	GroupPaymentCard(int balanceChange, MyVector<SharedPtr<Player>>& players);

	void printCardInfo() const override;
	bool applyEffect(SharedPtr<Player>& player) const override;
};

