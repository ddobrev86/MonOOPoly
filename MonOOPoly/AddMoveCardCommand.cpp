#include "AddMoveCardCommand.h"

void AddMoveCardCommand::execute(Monopoly* monopoly) const
{
    unsigned positions;
    std::cin >> positions;

    monopoly->addMoveCard(positions);

    system("cls");
    std::cout << "Movement Card added successfully\n";
}

Command* AddMoveCardCommand::clone() const
{
    return new AddMoveCardCommand(*this);
}
