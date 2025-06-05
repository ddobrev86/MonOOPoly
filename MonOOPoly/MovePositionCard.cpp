#include "MovePositionCard.h"

MovePositionCard::MovePositionCard(size_t positionsToMove, size_t boardSize)
{
	this->positionsToMove = positionsToMove;
	this->boardSize = boardSize;
}

void MovePositionCard::applyEffect(Player& player) const
{
	size_t newPos = (player.getPosition() + positionsToMove) % boardSize;
	player.moveTo(newPos);
}
