#include "Jail.h"

Jail::Jail() : CornerField()
{}

void Jail::printLandingMessage() const
{
    std::cout << "You have landed on Jail\n";
    system("pause");
    system("cls");
}

void Jail::printFieldInfo() const
{
    std::cout << "Jail";
}

bool Jail::action(SharedPtr<Player>& player)
{
    return true;
}