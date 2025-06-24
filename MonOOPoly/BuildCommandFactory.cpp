#include "BuildCommandFactory.h"
#include "BuildCommand.h"

Command* BuildCommandFactory::createCommand(const MyString& command, MyVector<SharedPtr<FieldFamily>>& validFamilies)
{
    if (command == "build")
        return new BuildCommand(validFamilies);

    return nullptr;
}
