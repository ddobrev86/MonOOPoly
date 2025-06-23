#include "AddFacilityCommand.h"

void AddFacilityCommand::execute(Monopoly* monopoly)
{
    MyString name;
    unsigned price;

    name.readLong();
    std::cin >> price;

    monopoly->addFacility(name, price);

    system("cls");
    std::cout << "Facility added successfully\n";
}

Command* AddFacilityCommand::clone() const
{
    return new AddFacilityCommand(*this);
}
