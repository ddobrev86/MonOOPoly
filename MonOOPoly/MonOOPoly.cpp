#include <iostream>
#include "Monopoly.h"

//TODO add Stations
//TODO add Facilities
//TODO add switchFields method in Monopoly class
//TODO add CornerFields
//TODO create default game
//TODO add Command
//TODO add CommandFactory
//TODO add FieldFactory
//TODO add PayAllCard
//TODO add FieldFamily -> child PropertyFamily
//TODO change buyMortgage logic from PropertyFamily to Property class
//TODO add Bank and Trade

int main()
{
	Monopoly* monopoly = Monopoly::getInstance(2, 11);

	PropertyFamily* browns = new PropertyFamily("Brown", 10, 20);
	browns->addProperty(SharedPtr<Property>(new Property("Old Kent Road", 10, 10)));
	browns->addProperty(SharedPtr<Property>(new Property("Whitechapel Road", 10, 10)));

	monopoly->addPropertyFamily(SharedPtr<PropertyFamily>(browns));
}