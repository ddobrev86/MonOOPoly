#include "AddPlayerCommand.h"

void AddPlayerCommand::execute(Monopoly* monopoly) const
{
    MyString username;
    username.readLong();

    monopoly->addPlayer(username);

    system("cls");
    std::cout << "Player added successfully\n";
}

Command* AddPlayerCommand::clone() const
{
    return new AddPlayerCommand(*this);
}
