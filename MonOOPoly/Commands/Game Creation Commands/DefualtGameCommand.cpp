#include "DefualtGameCommand.h"

void DefualtGameCommand::execute(Monopoly* monopoly) const
{
    unsigned playerCount;

    std::cout << "Enter player count: ";
    std::cin >> playerCount;

    monopoly = Monopoly::getInstance(playerCount, 11);
    monopoly->loadDefualtGame();
}

Command* DefualtGameCommand::clone() const
{
    return new DefualtGameCommand();
}
