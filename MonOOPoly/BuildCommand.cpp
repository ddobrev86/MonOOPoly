#include "BuildCommand.h"

BuildCommand::BuildCommand(bool& shouldBuild) : shouldBuild(shouldBuild)
{}

void BuildCommand::execute(Monopoly* monopoly) const
{
	MyString propertyName, mortgageType;
	std::cin >> mortgageType;
	propertyName.readLong();

	try
	{
		monopoly->actBuildCommand(propertyName, mortgageType);
		shouldBuild = false;
	}
	catch (const std::runtime_error& rntExcp)
	{
		shouldBuild = false;
		std::cout << rntExcp.what();
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