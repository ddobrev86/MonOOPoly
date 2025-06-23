#include "AddPropertyFamilyCommand.h"

void AddPropertyFamilyCommand::execute(Monopoly* monopoly)
{
    MyString name;
    unsigned cottageCost, castleCost;

    name.readLong();
    std::cin >> cottageCost >> castleCost;

    monopoly->addPropertyFamily(name, cottageCost, castleCost);

    system("cls");
    std::cout << "Property family added successfully\n";
}

Command* AddPropertyFamilyCommand::clone() const
{
    return nullptr;
}
