#include "BuildCommand.h"

void BuildCommand::execute(Monopoly* monopoly) const
{
	MyString propertyName, mortgageType;
	std::cin >> mortgageType;
	propertyName.readLong();
	
	monopoly->actBuildCommand(propertyName, mortgageType);
}

Command* BuildCommand::clone() const
{
	return new BuildCommand(*this);
}