#include "GoToJail.h"

GoToJail::GoToJail(size_t jailPosition) : CornerField()
{
    this->jailPosition = jailPosition;
}

void GoToJail::printLandingMessage() const
{
    std::cout << "You have landed on Go to Jail. Sorry!\n";
}

void GoToJail::printFieldInfo() const
{
    std::cout << "Go to Jail\n";
}

bool GoToJail::action(SharedPtr<Player>& player)
{
    player->goToJail();
    player->moveTo(jailPosition);
    return true;
    //TODO change position to prison;
}