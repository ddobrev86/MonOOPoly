#include "BuildCommand.h"

BuildCommand::BuildCommand(MyVector<SharedPtr<FieldFamily>>& validFamilies) : validFamilies(validFamilies)
{}

void BuildCommand::execute(Monopoly* monopoly)
{
	MyString propertyName, mortgageType;
	std::cin >> mortgageType;
	propertyName.readLong();

	try
	{
		monopoly->actBuildCommand(propertyName, mortgageType, validFamilies);
	}
	catch (const std::runtime_error& excp)
	{
		std::cout << excp.what() << '\n';
	}
	catch (const std::exception& excp)
	{
		throw excp;
	}
}

Command* BuildCommand::clone() const
{
	return new BuildCommand(*this);
}