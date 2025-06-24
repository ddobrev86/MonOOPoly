#include "AddStationCommand.h"

void AddStationCommand::execute(Monopoly* monopoly)
{
    MyString name;
    unsigned price, rent;

    //std::cout << "Enter station name: ";
    name.readLong();

    std::cout << "Enter price: ";
    std::cin >> price;

    std::cout << "Enter rent: ";
    std::cin >> rent;

    monopoly->addStation(name, price, rent);

    system("cls");
    std::cout << "Station added successfully\n";
}

Command* AddStationCommand::clone() const
{
    return new AddStationCommand(*this);
}
