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

void Monopoly::printBoard() const
{
	board->printBoard();
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
					throw std::invalid_argument("This Property Familty contains a property already on board");
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

size_t Monopoly::getPlayerCount() const
{
	return players.getSize();
}

void Monopoly::actPlayerAction()
{
	std::cout << "Player " << players[currentPlayer]->getUsername() << "\'s turn: \n";
	if (players[currentPlayer]->isInJail())
	{
		if (!getPlayerOutOfJail())
		{
			currentPlayer++;
			return;
		}
	}
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

bool Monopoly::throwPair() const
{
	int firstDice, secondDice;
	srand(time(0));

	firstDice = (rand() % 6) + 1;
	secondDice = (rand() % 6) + 1;

	std::cout << "You threw a " << firstDice << " and a " << secondDice << '\n';

	return firstDice == secondDice;
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
