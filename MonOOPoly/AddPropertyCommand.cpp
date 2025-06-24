#include "AddPropertyCommand.h"

void AddPropertyCommand::execute(Monopoly* monopoly)
{
    MyString propertyName, fieldFamily;
    unsigned price, rent;

    //std::cout << "Enter property name: ";
    propertyName.readLong();

    std::cout << "Enter family name: ";
    fieldFamily.readLong();

    std::cout << "Enter price: ";
    std::cin >> price;
    
    std::cout << "Enter rent: ";
    std::cin >> rent;

    monopoly->addProperty(fieldFamily, propertyName, price, rent);

    system("cls");
    std::cout << "Property added successfully\n";
}

Command* AddPropertyCommand::clone() const
{
    return new AddPropertyCommand(*this);
}
