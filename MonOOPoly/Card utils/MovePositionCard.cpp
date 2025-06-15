#include "MovePositionCard.h"

MovePositionCard::MovePositionCard(size_t positionsToMove, size_t boardSize)
{
	this->positionsToMove = positionsToMove;
	this->boardSize = boardSize;
}

void MovePositionCard::applyEffect(SharedPtr<Player>& player) const
{
	player->moveWith(positionsToMove, boardSize);
}
