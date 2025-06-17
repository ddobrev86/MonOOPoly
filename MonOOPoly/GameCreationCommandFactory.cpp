#include "GameCreationCommandFactory.h"

Command* GameCreationCommandFactory::createCommand(const MyString& command,
    bool& isDefault)
{
    if (command == "default")
    {
        isDefault = true;
        return new DefualtGameCommand();
    }
    else if (command == "manual")
    {
        isDefault = false;
        return new ManualGameCommand();
    }
    else if (command == "load")
    {
        isDefault = false;
        return new LoadGameCommand();
    }

    return nullptr;
}
