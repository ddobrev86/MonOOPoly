#include "Launcher.h"
#include "GameCommandFactory.h"
#include "GameElementsCommandFactory.h"
#include "GameCreationCommandFactory.h"
#include "CantAffordException.h"
#include "EndGameException.h"
#include "TradingCommandFactory.h"
#include "BuildCommandFactory.h"
#include "PendingPayment.h"
#include "GiveUpException.h"

void Launcher::run()
{
	Monopoly* monopoly = nullptr;
	MyString cmd = "";
	bool isDefault;

	startGame(monopoly, isDefault);
	system("cls");
	createElements(monopoly, isDefault);

	playGame(monopoly);
}

void Launcher::startGame(Monopoly* monopoly, bool& isDefault)
{
	MyString cmd;
	//system = Monopoly::getInstance();
	while (true)
	{
		printGameTypeOptions();

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
			printDefaultCreateElementsCommands();
		else
			printManualCreateElementsCommands();
		
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
			system("cls");
			std::cout << excp.what();
			break;
		}
		catch (const CantAffordException& excp)
		{
			std::cout << excp.what() << '\n';
			try
			{
				obligatoryTrade(monopoly, excp.getNeededAmount());
			}
			catch (const EndGameException& excp)
			{
				system("cls");
				std::cout << excp.what();
				break;
			}
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
		std::cout << i + 1 << ". ";
		ownedFields[i]->printUpForSaleMessage();
	}
}

void Launcher::obligatoryTrade(Monopoly* monopoly, int neededAmount)
{
	monopoly = Monopoly::getInstance();
	MyVector<SharedPtr<BuyableField>> ownedFields;
	size_t fieldPosition;

	monopoly->findOwnedFields(ownedFields);

	while (neededAmount > 0)
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

		std::cout << "Choose which property you want to sell (number).\nType 0 to give up: ";
		std::cin >> fieldPosition;

		if (fieldPosition == 0)
		{
			monopoly->playerExitGame();
			PendingPayment::clear();
			std::cout << "You have lost the game\n";
			system("pause");
			system("cls");
			return;
		}

		fieldPosition--;
		try
		{
			SharedPtr<BuyableField> fieldToSell = ownedFields[fieldPosition];
			trade(monopoly, fieldToSell, neededAmount);
			ownedFields.removeAt(fieldPosition);
		}
		catch (const EndGameException& excp)
		{
			throw excp;
		}
		catch (const GiveUpException& excp)
		{
			std::cout << excp.what() << '\n';
			monopoly->playerExitGame();
			PendingPayment::clear();

			system("pause");
			system("cls");
			return;
		}
		catch (const std::exception& excp)
		{
			system("cls");
			std::cout << "Type valid number!\n";
		}
	}

	PendingPayment::pay();

	std::cout << "\nYou have paid your dept\n";
	monopoly->goToNextPlayer();

	system("pause");
	system("cls");
}

void Launcher::trade(Monopoly* monopoly, SharedPtr<BuyableField>& fieldToTrade,
	int& neededAmount)
{
	MyString cmd;
	monopoly = Monopoly::getInstance();

	system("cls");
	while (true)
	{
		std::cout << "Needed amount: " << neededAmount << '\n';
		fieldToTrade->printUpForSaleMessage();

		std::cout << "\nPlayers that can afford to buy this property:\n";
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
		std::cout << "\t give_up\n";

		std::cout << "Enter command: ";
		std::cin >> cmd;

		if (cmd == "give_up")
			throw GiveUpException();


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

void Launcher::build(Monopoly* monopoly)
{
	MyString cmd;
	//monopoly = Monopoly::getInstance();

	MyVector<SharedPtr<FieldFamily>> validFamilies;
	monopoly->findValidFamilies(validFamilies);

	system("cls");
	while (true)
	{
		std::cout << "You can build on:\n";
		monopoly->printValidFamiliesMessage(validFamilies);

		std::cout << "\nChoose command: \n";
		std::cout << "\t1. build <mortgage_type> <property_name>\n";
		std::cout << "\t2. cancel\n";

		std::cout << "Enter command: ";
		std::cin >> cmd;

		if (cmd == "cancel")
			break;

		Command* command = BuildCommandFactory::createCommand(cmd, validFamilies);

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

void Launcher::printGameTypeOptions()
{
	std::cout << "Choose game type: \n";
	std::cout << "\t1. Start default game -> default\n";
	std::cout << "\t2. Enter board manually -> manual\n";
	//std::cout << "\t3. Load from file -> load\n";
}

void Launcher::printDefaultCreateElementsCommands()
{
	std::cout << "Choose option: \n";
	std::cout << "Add player -> add_player <username>\n";
	std::cout << "\nWhen ready, type start\n";
}

void Launcher::printManualCreateElementsCommands()
{
	std::cout << "Choose option: \n";
	std::cout << "\t1. Add player -> add_player <username>\n";
	std::cout << "\t2. Add property family -> add_property_family <family_name>\n";
	std::cout << "\t3. Add property -> add_property <property_name>\n";
	std::cout << "\t4. Add station -> add_station <station_name>\n";
	std::cout << "\t5. Add facility -> add_facility <facility_name>\n";
	std::cout << "\t6. Add card field -> add_card_field\n";
	std::cout << "\t7. Add movement card -> add_movement_card <positions_to_move>\n";
	std::cout << "\t8. Add payment card -> add_payment_card <amount_to_give>\n";
	std::cout << "\t9. Add group payment card -> add_group_payment_card <amount_to_give>\n";
	std::cout << "\nWhen ready, type start\n";
}