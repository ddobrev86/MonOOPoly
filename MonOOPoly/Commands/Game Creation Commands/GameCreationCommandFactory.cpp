#include "GameCreationCommandFactory.h"

Command* GameCreationCommandFactory::createCommand(const MyString& command)
{
    if (command == "default")
        return new DefualtGameCommand();
    else if (command == "manual")
        return new ManualGameCommand();
    else if (command == "load")
        return new LoadGameCommand();

    return nullptr;
}
