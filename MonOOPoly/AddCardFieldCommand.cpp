#include "AddCardFieldCommand.h"

void AddCardFieldCommand::execute(Monopoly* monopoly) const
{
    monopoly->addCardField();

    system("cls");
    std::cout << "Card Field added successfully\n";
}

Command* AddCardFieldCommand::clone() const
{
    return new AddCardFieldCommand(*this);
}
