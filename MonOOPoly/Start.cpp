#include "Start.h"
#include "Bank.h"

Start::Start() : CornerField()
{}

void Start::printLandingMessage() const
{
    std::cout << "You have landed on Start\n";
    std::cout << "You receive $200\n";
    system("pause");
    system("cls");
}

void Start::printFieldInfo() const
{
    std::cout << "Start";
}

bool Start::action(SharedPtr<Player>& player)
{
    Bank::landOnStart(player);
    return true;
}
