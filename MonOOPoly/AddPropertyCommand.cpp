#include "AddPropertyCommand.h"

void AddPropertyCommand::execute(Monopoly* monopoly) const
{
    MyString propertyName, fieldFamily;
    unsigned price, rent;

    fieldFamily.readLong();
    propertyName.readLong();
    std::cin >> price >> rent;

    monopoly->addProperty(fieldFamily, propertyName, price, rent);

    system("cls");
    std::cout << "Property added successfully\n";
}

Command* AddPropertyCommand::clone() const
{
    return new AddPropertyCommand(*this);
}
