#include "MovePositionCard.h"
#include "utilities.h"

MovePositionCard::MovePositionCard(int positionsToMove, size_t boardSize)
{
	this->positionsToMove = positionsToMove;
	this->boardSize = boardSize;
}

void MovePositionCard::printCardInfo() const
{
	std::cout << "You drew a Movement Card\n";
	std::cout << "Move with " << absoluteValue(positionsToMove) << " positions " << (positionsToMove > 0 ? "forwards" : "backwards") << "\n\n";
}

bool MovePositionCard::applyEffect(SharedPtr<Player>& player) const
{
	player->moveWith(positionsToMove, boardSize);
	return false;
}
