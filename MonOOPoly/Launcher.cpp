#include "Launcher.h"
#include "GameCommandFactory.h"
#include "GameElementsCommandFactory.h"
#include "GameCreationCommandFactory.h"

void Launcher::run()
{
	Monopoly* monopoly = nullptr;
	MyString cmd = "";

	startGame(monopoly);
	system("cls");
	createElements(monopoly);

	playGame(monopoly);
	//system("cls");
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

void Launcher::startGame(Monopoly* monopoly)
{
	MyString cmd;
	//system = Monopoly::getInstance();

	Monopoly::printGameTypeOptions();

	while (true)
	{

		std::cout << "Enter command: ";
		std::cin >> cmd;

		Command* command = GameCreationCommandFactory::createCommand(cmd);

		if (!command)
		{
			std::cout << "Invalid command\n\n";
			continue;
		}

		try
		{
			command->execute(monopoly);
			break;
		}
		catch (const std::exception& excp)
		{
			std::cout << excp.what() << '\n\n';
		}
	}
}

void Launcher::createElements(Monopoly* monopoly)
{
	MyString cmd;
	monopoly = Monopoly::getInstance();

	while (true)
	{
		Monopoly::printCreateElementsCommands();
		std::cout << "Enter command: ";
		std::cin >> cmd;

		if (cmd == "start")
		{
			try
			{
				monopoly->startGame();
				break;
			}
			catch (const std::exception& excp)
			{
				system("cls");
				std::cout << excp.what() << '\n';
				continue;
			}
		}

		Command* command = GameElementsCommandFactory::createCommand(cmd);

		if (!command)
		{
			system("cls");
			std::cout << "Invalid command\n";
			continue;
		}

		try
		{
			command->execute(monopoly);
		}
		catch (const std::exception& excp)
		{
			system("cls");
			std::cout << excp.what() << '\n';
		}
	}
}

void Launcher::playGame(Monopoly* monopoly)
{
	MyString cmd;
	monopoly = Monopoly::getInstance();

	while (true)
	{
		monopoly->printPlayersTurnMessage();
		std::cout << "Enter command: ";
		std::cin >> cmd;

		Command* command = GameCommandFactory::createCommand(cmd);

		if (!command)
		{
			std::cout << "Invalid command\n";
			continue;
		}

		system("cls");

		try
		{
			command->execute(monopoly);
		}
		catch (const std::exception& excp)
		{
			std::cout << excp.what() << '\n';
		}
	}
}
