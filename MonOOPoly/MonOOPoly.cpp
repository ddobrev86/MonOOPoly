#include <iostream>
#include "Monopoly.h"
#include "Station.h"
#include "Facility.h"

//-----TODO add Stations-----
//-----TODO add Facilities-----
//-----TODO add switchFields method in Monopoly class-----
//-----TODO add CornerFields-----
//-----TODO create default game-----
//-----TODO add Command-----
//TODO add CommandFactory
//TODO add FieldFactory
//TODO add PayAllCard
//-----TODO add FieldFamily -> child PropertyFamily-----
//-----TODO change buyMortgage logic from PropertyFamily to Property class-----
//TODO add Bank and Trade
//TODO make ransom, stations move change and start constants in a namespace
//TODO add Load From file

int main()
{
	Monopoly* monopoly = Monopoly::getInstance(2, 11);

	//monopoly->addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Brown", 10, 20)));
	//monopoly->addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Light Blue", 15, 30)));
	//monopoly->addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Pink", 25, 50)));
	//monopoly->addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Orange", 15, 30)));
	//monopoly->addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Red", 15, 30)));
	//monopoly->addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Yellow", 15, 30)));
	//monopoly->addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Green", 15, 30)));
	//monopoly->addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Dark Blue", 15, 30)));

	FieldFamily* browns = new PropertyFamily("Brown", 50, 50);
	FieldFamily* lightBlues = new PropertyFamily("Light Blue", 50, 50);
	FieldFamily* pinks = new PropertyFamily("Pink", 100, 100);
	FieldFamily* oranges = new PropertyFamily("Orange", 100, 100);
	FieldFamily* reds = new PropertyFamily("Red", 150, 150);
	FieldFamily* yellows = new PropertyFamily("Yellow", 150, 150);
	FieldFamily* greens = new PropertyFamily("Green", 200, 200);
	FieldFamily* darkBlues = new PropertyFamily("Dark Blue", 200, 200);
	FieldFamily* stations = new FieldFamily("Stations");
	FieldFamily* facilities = new FieldFamily("Facilities");

	browns->addField(SharedPtr<BuyableField>(new Property("Old Kent Road", 60, 80)));
	browns->addField(SharedPtr<BuyableField>(new Property("Whitechapel Road", 60, 100)));

	lightBlues->addField(SharedPtr<BuyableField>(new Property("The Angel, Islington", 100, 100)));
	lightBlues->addField(SharedPtr<BuyableField>(new Property("Euston Road", 100, 100)));
	lightBlues->addField(SharedPtr<BuyableField>(new Property("Pentonville Road", 120, 120)));

	pinks->addField(SharedPtr<BuyableField>(new Property("Pall Mall", 140, 120)));
	pinks->addField(SharedPtr<BuyableField>(new Property("Whitehall", 140, 120)));
	pinks->addField(SharedPtr<BuyableField>(new Property("Northumberland Avenue", 160, 140)));

	oranges->addField(SharedPtr<BuyableField>(new Property("Bow Street", 180, 140)));
	oranges->addField(SharedPtr<BuyableField>(new Property("Marlborough Street", 180, 140)));
	oranges->addField(SharedPtr<BuyableField>(new Property("Vine Street", 200, 160)));

	reds->addField(SharedPtr<BuyableField>(new Property("Strand", 220, 160)));
	reds->addField(SharedPtr<BuyableField>(new Property("Fleet Street", 220, 160)));
	reds->addField(SharedPtr<BuyableField>(new Property("Trafalgar Square", 240, 180)));

	yellows->addField(SharedPtr<BuyableField>(new Property("Leicester Square", 260, 180)));
	yellows->addField(SharedPtr<BuyableField>(new Property("Coventry Street", 260, 180)));
	yellows->addField(SharedPtr<BuyableField>(new Property("Piccadilly", 280, 200)));

	greens->addField(SharedPtr<BuyableField>(new Property("Regent Street", 300, 200)));
	greens->addField(SharedPtr<BuyableField>(new Property("Oxford Street", 300, 200)));
	greens->addField(SharedPtr<BuyableField>(new Property("Bond Street", 320, 220)));

	darkBlues->addField(SharedPtr<BuyableField>(new Property("Park Lane", 350, 250)));
	darkBlues->addField(SharedPtr<BuyableField>(new Property("Mayfair", 400, 300)));

	stations->addField(SharedPtr<BuyableField>(new Station("Kings Cross Station", 200, 25)));
	stations->addField(SharedPtr<BuyableField>(new Station("Marylebone Station", 200, 25)));
	stations->addField(SharedPtr<BuyableField>(new Station("Fenchurch St. Station", 200, 25)));
	stations->addField(SharedPtr<BuyableField>(new Station("Liverpool Street Station", 200, 25)));

	facilities->addField(SharedPtr<BuyableField>(new Facility("Electric Company", 150)));
	facilities->addField(SharedPtr<BuyableField>(new Facility("Water Works", 150)));

	monopoly->addFieldFamily(SharedPtr<FieldFamily>(browns));
	monopoly->addFieldFamily(SharedPtr<FieldFamily>(lightBlues));
	monopoly->addFieldFamily(SharedPtr<FieldFamily>(pinks));
	monopoly->addFieldFamily(SharedPtr<FieldFamily>(oranges));
	monopoly->addFieldFamily(SharedPtr<FieldFamily>(reds));
	monopoly->addFieldFamily(SharedPtr<FieldFamily>(yellows));
	monopoly->addFieldFamily(SharedPtr<FieldFamily>(greens));
	monopoly->addFieldFamily(SharedPtr<FieldFamily>(darkBlues));
	monopoly->addFieldFamily(SharedPtr<FieldFamily>(stations));
	monopoly->addFieldFamily(SharedPtr<FieldFamily>(facilities));
	monopoly->addCardFields(8);

	monopoly->randomiseBoard();
	monopoly->printBoard();
}