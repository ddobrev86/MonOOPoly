#include "ManualGameCommand.h"

void ManualGameCommand::execute(Monopoly* monopoly)
{
    unsigned playerCount, boardSize;

    std::cout << "Enter player count: ";
    std::cin >> playerCount;

    std::cout << "Enter board size: ";
    std::cin >> boardSize;

    monopoly = Monopoly::getInstance(playerCount, boardSize);
}

Command* ManualGameCommand::clone() const
{
    return new ManualGameCommand();
}