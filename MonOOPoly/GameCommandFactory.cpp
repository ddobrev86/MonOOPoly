#include "GameCommandFactory.h"
#include "BuildCommand.h"
#include "ThrowDiceCommand.h"
#include "BuyMortgageCommand.h"
#include "PrintOwnershipMapCommand.h"

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
        else if (command == "ownership_map")
            return new PrintOwnershipMapCommand();
    }

    return nullptr;
}
