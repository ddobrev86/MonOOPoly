#pragma once
#include "Card.h"

class MovePositionCard : public Card
{
private:
	int positionsToMove;
	size_t boardSize;
public:
	MovePositionCard(int positionsToMove, size_t boardSize);

	void printCardInfo() const override;
	void applyEffect(SharedPtr<Player>& player) const override;
};

