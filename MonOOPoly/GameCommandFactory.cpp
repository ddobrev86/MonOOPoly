#include "GameCommandFactory.h"

bool GameCommandFactory::shouldBuild = false;

Command* GameCommandFactory::createCommand(const MyString& command)
{
    if (shouldBuild)
    {
        if (command == "build")
            return new BuildCommand(shouldBuild);
    }
    else
    {
        if (command == "throw_dice")
            return new ThrowDiceCommand();
        else if (command == "buy_mortgage")
            return new BuyMortgageCommand(shouldBuild);
    }

    return nullptr;
}
