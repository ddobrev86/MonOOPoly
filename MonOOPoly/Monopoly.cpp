#include "Monopoly.h"
#include <stdlib.h>
#include <ctime>
#include "InputProcessor.h"

Monopoly* Monopoly::instance = nullptr;

Monopoly::Monopoly(size_t playerCount, size_t boardSize)
{
	//this->playerCount = playerCount;
	players = MyVector<SharedPtr<Player>>(playerCount);
	board = UniquePtr<Board>(new Board(boardSize));
	currentPlayer = 0;
}

Monopoly* Monopoly::getInstance(size_t playerCount, size_t boardSize)
{
	if (!instance)
	{
		if (playerCount < GameConstants::MIN_PLAYER_COUNT 
			|| playerCount > GameConstants::MAX_PLAYER_COUNT)
				throw std::invalid_argument("Invalid player count");

		instance = new Monopoly(playerCount, boardSize);

	}
	return instance;
}

void Monopoly::printGameTypeOptions()
{
	std::cout << "Choose game type: \n";
	std::cout << "\t1. Start default game -> default\n";
	std::cout << "\t2. Enter board manually -> manual\n";
	std::cout << "\t3. Load from file -> load\n";
	

}

void Monopoly::printBoard() const
{
	board->printBoard();
}

void Monopoly::randomiseBoard()
{
	board->randomiseBoard();
}

void Monopoly::switchFields(size_t firstIndex, size_t secondIndex)
{
	board->switchFields(firstIndex, secondIndex);
}

void Monopoly::addCardFields(size_t count)
{
	board->addCardFields(count);
}

void Monopoly::addPlayer(const SharedPtr<Player>& player)
{
	if (players.getSize() == GameConstants::MAX_PLAYER_COUNT)
		throw std::runtime_error("Max player count reached");

	for (size_t i = 0; i < players.getSize(); i++)
	{
		if (players[i]->compareUsername(player))
			throw std::invalid_argument("There already is a player with this username");
	}
	players.push_back(player);
}

void Monopoly::addPlayer(const MyString& username)
{
	addPlayer(SharedPtr<Player>(new Player(username)));
}

bool Monopoly::canAddFieldFamily(const SharedPtr<FieldFamily>& fieldFamily,
	UniquePtr<Iterator<SharedPtr<BuyableField>>>& mainIterator)
{
	UniquePtr<Iterator<SharedPtr<BuyableField>>> secondaryIterator;

	while (mainIterator->hasNext())
	{
		SharedPtr<BuyableField> currentField = mainIterator->next();

		for (size_t currentFamily = 0; currentFamily < fieldFamilies.getSize(); currentFamily++)
		{
			secondaryIterator = std::move(fieldFamilies[currentFamily]->createIterator());
			while (secondaryIterator->hasNext())
			{
				if (currentField.compareWith(secondaryIterator->next()))
					throw std::invalid_argument("This Field Familty contains a field already on board");
			}
		}
	}

	return true;
}

void Monopoly::addFieldFamily(const SharedPtr<FieldFamily>& fieldFamily)
{
	UniquePtr<Iterator<SharedPtr<BuyableField>>> mainIterator(fieldFamily->createIterator());

	if (canAddFieldFamily(fieldFamily, mainIterator))
	{
		mainIterator->toStart();
		while (mainIterator->hasNext())
		{
			SharedPtr<Field> placeholder(mainIterator->next().get());
			board->addField(placeholder);
		}

		fieldFamilies.push_back(fieldFamily);
	}
}

void Monopoly::addField(const SharedPtr<Field>& field)
{
	board->addField(field);
}

size_t Monopoly::getPlayerCount() const
{
	return players.getSize();
}

void Monopoly::printPlayersTurnMessage()
{
	std::cout << "Player " << players[currentPlayer]->getUsername() << "\'s turn\n";
	
	if (players[currentPlayer]->isInJail())
	{
		if (!getPlayerOutOfJail())
		{
			currentPlayer++;
			return;
		}
	}

	std::cout << "Choose action: \n";
	std::cout << "\t1. throw_dice\n";
	std::cout << "\t2. buy_mortgage\n";
	std::cout << "\t3. trade\n";
}

//throw_dice
void Monopoly::actPlayerThrowDiceCommand()
{
	movePlayer();

	SharedPtr<Field>& currentField = board->operator[](players[currentPlayer]->getPosition());
	currentField->printFieldInfo();
	fieldActionUntilSuccess(currentField);

	currentPlayer++;
}

void Monopoly::fieldActionUntilSuccess(SharedPtr<Field>& currentField)
{
	do
	{
		bool success = currentField->action(players[currentPlayer]);
		players[currentPlayer]->moveWith(0, board->getTotalSize());
		if (success)
			break;

		currentField = board->operator[](players[currentPlayer]->getPosition());

	} while (true);
}

size_t Monopoly::throwDice() const
{
	int firstDice, secondDice;
	srand(time(0));

	firstDice = (rand() % 6) + 1;
	secondDice = (rand() % 6) + 1;

	std::cout << "You threw a " << firstDice << " and a " << secondDice << '\n';

	return firstDice + secondDice;
}

void Monopoly::movePlayer()
{
	size_t positions = throwDice();
	players[currentPlayer]->moveWith(positions, board->getTotalSize());
}

//buy_mortgage
void Monopoly::actBuyMortgageCommand()
{
	MyVector<SharedPtr<FieldFamily>> validFamilies;
	bool canBuy = false;

	findValidFamilies(validFamilies, canBuy);

	if (!canBuy)
		throw std::runtime_error("You can't buy any mortgages");
	
	printValidFamiliesMessage(validFamilies);
}

void Monopoly::findValidFamilies(MyVector<SharedPtr<FieldFamily>>& validFamilies,
	bool& canBuy)
{
	for (size_t i = 0; i < fieldFamilies.getSize(); i++)
	{
		if (fieldFamilies[i]->canBuyMortgages() &&
			fieldFamilies[i]->ownsAll(players[currentPlayer]))
		{
			validFamilies.push_back(fieldFamilies[i]);
			canBuy = true;
		}
	}
}

void Monopoly::printValidFamiliesMessage(const MyVector<SharedPtr<FieldFamily>>& validFamilies) const
{
	std::cout << "Choose one of the following properties and the type of mortgage";
	std::cout << "\nFormat: build <mortgage_type> <property_name>";
	for (size_t i = 0; i < validFamilies.getSize(); i++)
	{
		validFamilies[i]->printFamilyInfo();
		std::cout << '\n';
	}
}

//build
void Monopoly::actBuildCommand(const MyString& propertyName, 
	const MyString& mortgageType)
{
	MyVector<SharedPtr<FieldFamily>> validFamilies;
	bool canBuy = false;
	findValidFamilies(validFamilies, canBuy);

	UniquePtr<Iterator<SharedPtr<BuyableField>>> fieldIterator;

	for (size_t i = 0; i < validFamilies.getSize(); i++)
	{
		fieldIterator = std::move(validFamilies[i]->createIterator());

		while (fieldIterator->hasNext())
		{
			SharedPtr<BuyableField> current = fieldIterator->next();
			if (current->compareName(propertyName))
			{
				current->buildMortgage(mortgageType);
				std::cout << "You successfully built a " << mortgageType;
				return;
			}
		}
	}

	throw std::invalid_argument("Wrong property name");
}

//in Jail
bool Monopoly::throwPair() const
{
	int firstDice, secondDice;
	srand(time(0));

	firstDice = (rand() % 6) + 1;
	secondDice = (rand() % 6) + 1;

	std::cout << "You threw a " << firstDice << " and a " << secondDice << '\n';

	return firstDice == secondDice;
}

bool Monopoly::getPlayerOutOfJail()
{
	std::cout << "You are in jail.\n";
	if (players[currentPlayer]->getRemainingToRansom())
	{
		std::cout << "You have to wait "
			<< players[currentPlayer]->getRemainingToRansom()
			<< " turns to be able to pay to get out\n";
	}
	else
	{
		std::cout << "Do you want to pay $100 to get out of jail?(y|n): ";
		if (InputProcessor::askYesOrNo() == 'y')
		{
			players[currentPlayer]->removeFromBalance(100);
			players[currentPlayer]->getOutOfJail();
			return true;
		}
	}

	bool isPair = throwPair();
	if (!isPair)
	{
		std::cout << "You have to stay in jail for one more turn\n";
		return false;
	}
	else
	{
		std::cout << "You got out of jail!\n";
		players[currentPlayer]->getOutOfJail();
		return true;
	}
}
