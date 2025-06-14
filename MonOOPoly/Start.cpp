#include "Start.h"

Start::Start() : CornerField()
{}

void Start::printLandingMessage() const
{
    std::cout << "You have landed on Start\n";
    std::cout << "You receive $200";
}

void Start::printFieldInfo() const
{
    std::cout << "Start";
}

bool Start::action(SharedPtr<Player>& player)
{
    player->addToBalance(200);
}
