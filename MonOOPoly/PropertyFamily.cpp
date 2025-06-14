#include "PropertyFamily.h"

PropertyFamily::PropertyFamily(const MyString& name,
	unsigned cottagePrice, unsigned castlePrice) : FieldFamily(name)
{
	//this->name = name;
	cottage = SharedPtr<Mortgage>(new Cottage(cottagePrice));
	castle = SharedPtr<Mortgage>(new Castle(castlePrice));
}

void PropertyFamily::addField(SharedPtr<BuyableField>& field)
{
	field->setUpMortgages(castle, cottage);
	FieldFamily::addField(field);
}

void PropertyFamily::addField(SharedPtr<BuyableField>&& field)
{
	field->setUpMortgages(castle, cottage);
	FieldFamily::addField(field);
}

void PropertyFamily::printFamilyInfo() const
{
	std::cout << name << '\n';
	std::cout << "Cottage cost: " << cottage->getPrice() 
		<< '\t' << "Castle cost: " << castle->getPrice() << '\n';
		
	for (size_t i = 0; i < data.getSize(); i++)
	{
		std::cout << '\t';
		data[i]->printFieldInfo();
		std::cout << '\n';
	}
}

//bool PropertyFamily::containsProperty(const SharedPtr<Property>& property)
//{
//	for (size_t i = 0; i < data.getSize(); i++)
//	{
//		if (data[i].compareWith(property))
//			return true;
//	}
//	return false;
//}
//size_t PropertyFamily::howManyBelongToPlayer(const SharedPtr<Player>& player)
//{
//	size_t count = 0;
//	for (size_t i = 0; i < data.getSize(); i++)
//	{
//		if (data[i]->belongsToPlayer(player))
//			count++;
//	}
//
//	return count;
//}
//
//bool PropertyFamily::ownsAll(const SharedPtr<Player>& player)
//{
//	for (size_t i = 0; i < data.getSize(); i++)
//	{
//		if (!data[i]->belongsToPlayer(player))
//			return false;
//	}
//
//	return true;
//}

//void PropertyFamily::buyProperty(const SharedPtr<Player>& player, bool isCottage)
//{
//	if (!ownsAll(player))
//		throw std::logic_error("You cannot buy mortgages - you don't own all properties of this color!");
//
//	if (isCottage)
//	{
//		mortgages->buyMortgage(SharedPtr<Mortgage>(cottage));
//	}
//	else
//	{
//		if (!mortgages->canBuyCastle())
//			throw std::runtime_error("You don't have the minimum cottages to buy a castle");
//
//		mortgages->buyMortgage(SharedPtr<Mortgage>(castle));
//
//	}
//}
