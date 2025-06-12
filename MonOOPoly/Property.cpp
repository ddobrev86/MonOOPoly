#include "Property.h"
#include "InputProcessor.h"

Property::Property(const MyString& name, unsigned price, unsigned rent) : BuyableField(name, price, rent)
{}

//bool Property::belongsToPlayer(const SharedPtr<Player>& player)
//{
//	if (isFree())
//		return false;
//
//	return owner.compareWith(player);
//}
//
//bool Property::isFree() const
//{
//	return !owner.isInitalized();
//}
//void Property::printFieldInfo() const
//{
//	std::cout << "You have landed on " << name << '\n';
//
//	if (isFree())
//	{
//		std::cout << "No one owns this property. You can buy it!\n";
//		std::cout << "It costs " << price << '\n';
//	}
//	else
//	{
//		std::cout << "This property belongs to " << owner->getUsername() << '\n';
//		std::cout << "Rent: " << mortgageManager->getTotalRent(rent) << '\n';
//	}
//}

void Property::buyMortgage()
{

}

size_t Property::calculateTotalRent() const
{
	return mortgageManager->getTotalRent(rent);
}
