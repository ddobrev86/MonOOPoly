#include "Jail.h"

Jail::Jail() : CornerField()
{}

void Jail::printLandingMessage() const
{
    std::cout << "You have landed on Jail\n";
}

void Jail::printFieldInfo() const
{
    std::cout << "Jail\n";
}

bool Jail::action(SharedPtr<Player>& player)
{
    return true;
}