#pragma once
#include "Card.h"

class MovePositionCard : public Card
{
private:
	size_t positionsToMove;
	size_t boardSize;
public:
	MovePositionCard(size_t positionsToMove, size_t boardSize);

	void applyEffect(SharedPtr<Player>& player) const override;
};

