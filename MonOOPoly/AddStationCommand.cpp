#include "AddStationCommand.h"

void AddStationCommand::execute(Monopoly* monopoly)
{
    MyString name;
    unsigned price, rent;

    name.readLong();
    std::cin >> price >> rent;

    monopoly->addStation(name, price, rent);

    system("cls");
    std::cout << "Station added successfully\n";
}

Command* AddStationCommand::clone() const
{
    return new AddStationCommand(*this);
}
