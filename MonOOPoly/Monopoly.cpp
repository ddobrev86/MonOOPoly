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

Monopoly* Monopoly::getInstance(size_t playerCount = Constants::MIN_PLAYER_COUNT,
	size_t boardSize = Constants::STANDART_BOARD_SIZE)
{
	if (!instance)
		instance = new Monopoly(playerCount, boardSize);

	return instance;
}

void Monopoly::addPlayer(const SharedPtr<Player>& player)
{
	if (players.getSize() == Constants::MAX_PLAYER_COUNT)
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

	currentPlayer++;
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
	players[currentPlayer]->moveWith(positions);
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
		std::cout << "You got out of jail!";
		players[currentPlayer]->getOutOfJail();
		return false;
	}
}
