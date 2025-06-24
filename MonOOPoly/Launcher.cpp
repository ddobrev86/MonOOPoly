#include "Launcher.h"
#include "GameCommandFactory.h"
#include "GameElementsCommandFactory.h"
#include "GameCreationCommandFactory.h"
#include "CantAffordException.h"
#include "EndGameException.h"
#include "TradingCommandFactory.h"

void Launcher::run()
{
	Monopoly* monopoly = nullptr;
	MyString cmd = "";
	bool isDefault;

	startGame(monopoly, isDefault);
	system("cls");
	createElements(monopoly, isDefault);

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

void Launcher::startGame(Monopoly* monopoly, bool& isDefault)
{
	MyString cmd;
	//system = Monopoly::getInstance();
	while (true)
	{
		Monopoly::printGameTypeOptions();

		std::cout << "Enter command: ";
		std::cin >> cmd;

		Command* command = GameCreationCommandFactory::createCommand(cmd, isDefault);

		if (!command)
		{
			std::cout << "Invalid command\n\n";
			system("pause");
			system("cls");

			continue;
		}

		try
		{
			command->execute(monopoly);
			break;
		}
		catch (const std::exception& excp)
		{
			std::cout << excp.what() << "\n\n";

			system("pause");
			system("cls");
		}
	}
}

void Launcher::createElements(Monopoly* monopoly, bool isDefault)
{
	MyString cmd;
	monopoly = Monopoly::getInstance();

	while (true)
	{
		if (isDefault)
			Monopoly::printDefaultCreateElementsCommands();
		else
			Monopoly::printManualCreateElementsCommands();
		
		std::cout << "Enter command: ";
		std::cin >> cmd;

		if (cmd == "start")
		{
			try
			{
				system("cls");
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
			system("cls");
			std::cout << "Invalid command\n";

			system("pause");
			system("cls");
			continue;
		}

		system("cls");

		try
		{
			//system("cls");
			command->execute(monopoly);
		}
		catch(const EndGameException& excp)
		{
			std::cout << excp.what();
			break;
		}
		catch (const CantAffordException& excp)
		{
			std::cout << excp.what() << '\n';
			obligatoryTrade(monopoly, excp.getNeededAmount());
		}
		catch (const std::exception& excp)
		{
			//system("cls");
			std::cout << excp.what() << '\n';

			monopoly->goToNextPlayer();
			system("pause");
			system("cls");
		}
	}
}

void Launcher::printFieldsToTradeMessage(const MyVector<SharedPtr<BuyableField>>& ownedFields, int neededAmount)
{
	std::cout << "You have to get $" << neededAmount << "\nYou own:\n";
	for (size_t i = 0; i < ownedFields.getSize(); i++)
	{
		std::cout << i + 1 << ". " << ownedFields[i]->getName() << '\n';
		std::cout << "\tPrice to bank: " << ownedFields[i]->sellPriceToBank()
			<< "\tPrice to player: " << ownedFields[i]->sellPriceToPlayer() << '\n';
	}
}

void Launcher::obligatoryTrade(Monopoly* monopoly, int neededAmount)
{
	monopoly = Monopoly::getInstance();
	MyVector<SharedPtr<BuyableField>> ownedFields;
	size_t fieldPosition;

	monopoly->findOwnedFields(ownedFields);

	while (neededAmount)
	{
		if (ownedFields.isEmpty())
		{
			std::cout << "You have nothing to sell - you have gone bankrupt!\n";
			monopoly->playerExitGame();

			system("pause");
			system("cls");

			return;
		}

		printFieldsToTradeMessage(ownedFields, neededAmount);

		std::cout << "Choose which property you want to sell (number): ";
		std::cin >> fieldPosition;
		fieldPosition--;

		try
		{
			SharedPtr<BuyableField> fieldToSell = ownedFields[fieldPosition];
			ownedFields.removeAt(fieldPosition);
			trade(monopoly, fieldToSell, neededAmount);
		}
		catch (const std::exception& excp)
		{
			system("cls");
			std::cout << "Type valid number!\n";
		}
	}
}

void Launcher::trade(Monopoly* monopoly, SharedPtr<BuyableField>& fieldToTrade,
	int& neededAmount)
{
	MyString cmd;
	monopoly = Monopoly::getInstance();

	while (true)
	{
		std::cout << "Players that can afford to buy this property:\n";
		try
		{
			monopoly->printPlayersThatCanAfford(fieldToTrade->sellPriceToPlayer());
		}
		catch(const std::runtime_error& excp)
		{
			std::cout << excp.what() << '\n';
			system("pause");
			system("cls");

			continue;
		}

		std::cout << "\nChoose option: \n";
		std::cout << "\ttrade_with_bank\n";
		std::cout << "\ttrade_with_player <username>\n";

		std::cout << "Enter command: ";
		std::cin >> cmd;

		Command* command = TradingCommandFactory::createCommand(cmd, fieldToTrade, neededAmount);

		if (!command)
		{
			system("cls");
			std::cout << "Invalid command\n";

			system("pause");
			system("cls");
			continue;
		}

		try
		{
			command->execute(monopoly);
			break;
		}
		catch (const std::exception& excp)
		{
			system("cls");
			std::cout << excp.what() << '\n';

			system("pause");
			system("cls");
		}
	}
}
