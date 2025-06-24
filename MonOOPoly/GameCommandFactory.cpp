#include "GameCommandFactory.h"
#include "BuildCommand.h"
#include "ThrowDiceCommand.h"
#include "BuyMortgageCommand.h"
#include "PrintOwnershipMapCommand.h"

bool GameCommandFactory::shouldBuild = false;

Command* GameCommandFactory::createCommand(const MyString& command)
{
    if (command == "throw_dice")
        return new ThrowDiceCommand();
    else if (command == "buy_mortgage")
        return new BuyMortgageCommand();
    else if (command == "ownership_map")
        return new PrintOwnershipMapCommand();

    /*if (shouldBuild)
    {
        if (command == "build")
            return new BuildCommand();
    }
    else
    {
        if (command == "throw_dice")
            return new ThrowDiceCommand();
        else if (command == "buy_mortgage")
            return new BuyMortgageCommand();
        else if (command == "ownership_map")
            return new PrintOwnershipMapCommand();
    }*/

    return nullptr;
}
