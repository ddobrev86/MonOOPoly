#include "AddPlayerCommand.h"

void AddPlayerCommand::execute(Monopoly* monopoly)
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
