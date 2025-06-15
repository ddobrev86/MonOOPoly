#include "Monopoly.h"
#include <stdlib.h>
#include <ctime>
#include "InputProcessor.h"
#include "Station.h"
#include "Facility.h"
#include "Bank.h"
#include "Trade.h"

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

Monopoly* Monopoly::getInstance()
{
	if (!instance)
		throw std::logic_error("Game isn't initialised yet");

	return instance;
}

void Monopoly::printGameTypeOptions()
{
	std::cout << "Choose game type: \n";
	std::cout << "\t1. Start default game -> default\n";
	std::cout << "\t2. Enter board manually -> manual\n";
	std::cout << "\t3. Load from file -> load\n";
}

void Monopoly::loadDefualtGame()
{
	FieldFamily* browns = new PropertyFamily("Brown", 50, 50);
	FieldFamily* lightBlues = new PropertyFamily("Light Blue", 50, 50);
	FieldFamily* pinks = new PropertyFamily("Pink", 100, 100);
	FieldFamily* oranges = new PropertyFamily("Orange", 100, 100);
	FieldFamily* reds = new PropertyFamily("Red", 150, 150);
	FieldFamily* yellows = new PropertyFamily("Yellow", 150, 150);
	FieldFamily* greens = new PropertyFamily("Green", 200, 200);
	FieldFamily* darkBlues = new PropertyFamily("Dark Blue", 200, 200);
	FieldFamily* stations = new FieldFamily("Stations");
	FieldFamily* facilities = new FieldFamily("Facilities");

	browns->addField(SharedPtr<BuyableField>(new Property("Old Kent Road", 60, 80)));
	browns->addField(SharedPtr<BuyableField>(new Property("Whitechapel Road", 60, 100)));

	lightBlues->addField(SharedPtr<BuyableField>(new Property("The Angel, Islington", 100, 100)));
	lightBlues->addField(SharedPtr<BuyableField>(new Property("Euston Road", 100, 100)));
	lightBlues->addField(SharedPtr<BuyableField>(new Property("Pentonville Road", 120, 120)));

	pinks->addField(SharedPtr<BuyableField>(new Property("Pall Mall", 140, 120)));
	pinks->addField(SharedPtr<BuyableField>(new Property("Whitehall", 140, 120)));
	pinks->addField(SharedPtr<BuyableField>(new Property("Northumberland Avenue", 160, 140)));

	oranges->addField(SharedPtr<BuyableField>(new Property("Bow Street", 180, 140)));
	oranges->addField(SharedPtr<BuyableField>(new Property("Marlborough Street", 180, 140)));
	oranges->addField(SharedPtr<BuyableField>(new Property("Vine Street", 200, 160)));

	reds->addField(SharedPtr<BuyableField>(new Property("Strand", 220, 160)));
	reds->addField(SharedPtr<BuyableField>(new Property("Fleet Street", 220, 160)));
	reds->addField(SharedPtr<BuyableField>(new Property("Trafalgar Square", 240, 180)));

	yellows->addField(SharedPtr<BuyableField>(new Property("Leicester Square", 260, 180)));
	yellows->addField(SharedPtr<BuyableField>(new Property("Coventry Street", 260, 180)));
	yellows->addField(SharedPtr<BuyableField>(new Property("Piccadilly", 280, 200)));

	greens->addField(SharedPtr<BuyableField>(new Property("Regent Street", 300, 200)));
	greens->addField(SharedPtr<BuyableField>(new Property("Oxford Street", 300, 200)));
	greens->addField(SharedPtr<BuyableField>(new Property("Bond Street", 320, 220)));

	darkBlues->addField(SharedPtr<BuyableField>(new Property("Park Lane", 350, 250)));
	darkBlues->addField(SharedPtr<BuyableField>(new Property("Mayfair", 400, 300)));

	stations->addField(SharedPtr<BuyableField>(new Station("Kings Cross Station", 200, 25)));
	stations->addField(SharedPtr<BuyableField>(new Station("Marylebone Station", 200, 25)));
	stations->addField(SharedPtr<BuyableField>(new Station("Fenchurch St. Station", 200, 25)));
	stations->addField(SharedPtr<BuyableField>(new Station("Liverpool Street Station", 200, 25)));

	facilities->addField(SharedPtr<BuyableField>(new Facility("Electric Company", 150)));
	facilities->addField(SharedPtr<BuyableField>(new Facility("Water Works", 150)));

	addFieldFamily(SharedPtr<FieldFamily>(browns));
	addFieldFamily(SharedPtr<FieldFamily>(lightBlues));
	addFieldFamily(SharedPtr<FieldFamily>(pinks));
	addFieldFamily(SharedPtr<FieldFamily>(oranges));
	addFieldFamily(SharedPtr<FieldFamily>(reds));
	addFieldFamily(SharedPtr<FieldFamily>(yellows));
	addFieldFamily(SharedPtr<FieldFamily>(greens));
	addFieldFamily(SharedPtr<FieldFamily>(darkBlues));
	addFieldFamily(SharedPtr<FieldFamily>(stations));
	addFieldFamily(SharedPtr<FieldFamily>(facilities));
	addCardFields(8);

	randomiseBoard();
	printBoard();
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

	SharedPtr<BuyableField> field = findBuyableField(validFamilies, propertyName);
	field->buildMortgage(mortgageType);
	std::cout << "You successfully built a " << mortgageType;
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
			Bank::getFrom(players[currentPlayer], 100);
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

void Monopoly::tradeBetweenPlayers(const MyString& receiverName, 
	const MyString& propertyName)
{
	if (players[currentPlayer]->compareUsername(receiverName))
		throw std::invalid_argument("You can't trade with yourself");

	SharedPtr<BuyableField> field = findBuyableField(fieldFamilies, propertyName);
	SharedPtr<Player> receiver = findPlayer(receiverName);
	
	Trade::sellToPlayer(players[currentPlayer], receiver, field);
}

void Monopoly::tradeWithBank(const MyString& propertyName)
{
	SharedPtr<BuyableField> field = findBuyableField(fieldFamilies, propertyName);
	Trade::sellToBank(players[currentPlayer], field);
}

SharedPtr<BuyableField>& Monopoly::findBuyableField(const MyVector<SharedPtr<FieldFamily>>& families,
	const MyString& propertyName)
{
	UniquePtr<Iterator<SharedPtr<BuyableField>>> fieldIterator;

	for (size_t i = 0; i < families.getSize(); i++)
	{
		fieldIterator = std::move(families[i]->createIterator());

		while (fieldIterator->hasNext())
		{
			SharedPtr<BuyableField> current = fieldIterator->next();
			if (current->compareName(propertyName))
				return current;
		}
	}

	throw std::invalid_argument("Wrong property name");
}

SharedPtr<Player>& Monopoly::findPlayer(const MyString& playerName)
{
	for (size_t i = 0; i < players.getSize(); i++)
	{
		if (players[i]->compareUsername(playerName))
			return players[i];
	}

	throw std::invalid_argument("Invalid username");
}
