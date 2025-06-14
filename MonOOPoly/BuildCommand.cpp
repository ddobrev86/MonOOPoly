#include "BuildCommand.h"

void BuildCommand::execute(Monopoly* monopoly) const
{
	MyString propertyName, mortgageType;
	std::cin >> mortgageType;
	propertyName.readLong();


	
	//monopoly->actPlayerThrowDiceCommand();
}

Command* BuildCommand::clone() const
{
	return new BuildCommand(*this);
}