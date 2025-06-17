#include "Start.h"
#include "Bank.h"

Start::Start() : CornerField()
{}

void Start::printLandingMessage() const
{
    std::cout << "You have landed on Start\n";
    std::cout << "You receive $200";
}

void Start::printFieldInfo() const
{
    std::cout << "Start\n";
}

bool Start::action(SharedPtr<Player>& player)
{
    Bank::giveTo(player, 200);
    return true;
}
