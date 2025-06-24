#include "AddMoveCardCommand.h"

void AddMoveCardCommand::execute(Monopoly* monopoly)
{
    unsigned positions;

    //std::cout << "Enter positions to move(positive or negative): ";
    std::cin >> positions;

    monopoly->addMoveCard(positions);

    system("cls");
    std::cout << "Movement Card added successfully\n";
}

Command* AddMoveCardCommand::clone() const
{
    return new AddMoveCardCommand(*this);
}
