#include "GoToJail.h"

GoToJail::GoToJail() : CornerField()
{}

void GoToJail::printLandingMessage() const
{
    std::cout << "You have landed on Go to Jail. Sorry!\n";
}

void GoToJail::printFieldInfo() const
{
    std::cout << "Go to Jail";
}

bool GoToJail::action(SharedPtr<Player>& player)
{
    player->goToJail();
    //TODO change position to prison;
}