#include "Launcher.h"
#include "GameCommandFactory.h"
#include "GameCreationCommandFactory.h"

void Launcher::run()
{
	Monopoly* system = nullptr;
	MyString cmd = "";

	startGame(system);

	/*while (true)
	{
		Monopoly::printGameTypeOptions();

		std::cout << "Enter command: ";
		std::cin >> cmd;

		if (cmd == "end")
		{
			delete system;
			system = nullptr;
			break;
		}

		Command* command = CommandFactory::createCommand(cmd);

		if (!command)
		{
			std::cout << "Invalid command\n";
		}
		else
		{
			command->execute(system);
		}

		std::cout << "\n\n";
	}*/
}

void Launcher::startGame(Monopoly* system)
{
	MyString cmd;

	Monopoly::printGameTypeOptions();

	while (true)
	{

		std::cout << "Enter command: ";
		std::cin >> cmd;

		Command* command = GameCreationCommandFactory::createCommand(cmd);

		if (!command)
		{
			std::cout << "Invalid command\n";
			continue;
		}

		try
		{
			command->execute(system);
			break;
		}
		catch (const std::exception& excp)
		{
			std::cout << excp.what() << '\n';
		}
	}
}

void Launcher::playGame(Monopoly* system)
{
	MyString cmd;

	while (true)
	{
		system->printPlayersTurnMessage();
		std::cout << "Enter command: ";
		std::cin >> cmd;

		Command* command = GameCommandFactory::createCommand(cmd);

		if (!command)
		{
			std::cout << "Invalid command\n";
			continue;
		}

		try
		{
			command->execute(system);
			break;
		}
		catch (const std::exception& excp)
		{
			std::cout << excp.what() << '\n';
		}
	}
}
