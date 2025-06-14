#include "GameCommandFactory.h"

Command* GameCommandFactory::createCommand(const MyString& command)
{
    if (command == "throw_dice")
        return new ThrowDiceCommand();
    else if (command == "buy_mortgage")
        return new BuyMortgageCommand();
    else if (command == "build")
        return new BuildCommand();

    return nullptr;
}
