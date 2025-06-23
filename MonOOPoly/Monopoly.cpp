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
	board = UniquePtr<Board>(new Board(boardSize));
	players = MyVector<SharedPtr<Player>>(playerCount);
	currentPlayer = 0;
	this->playerCount = playerCount;
	deck = SharedPtr<CardDeck>(new CardDeck());

	hasStations = false;
	hasFacilities = false;
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
	//std::cout << "\t When ready, type start\n";
}

void Monopoly::printDefaultCreateElementsCommands()
{
	std::cout << "Choose option: \n";
	std::cout << "Add player -> add_player <username>\n";
	//std::cout << "\t2. Add movement card-> add_movement_card <positions_to_move>\n";
	//std::cout << "\t3. Add payment card -> add_payment_card <value>\n";
	std::cout << "\nWhen ready, type start\n";
}

void Monopoly::printManualCreateElementsCommands()
{
	std::cout << "Choose option: \n";
	std::cout << "\t1. Add player -> add_player <username>\n";
	std::cout << "\t2. Add property family -> add_property_family <family_name> <cottage_price> <castle_price>\n";
	std::cout << "\t3. Add property -> add_property <property_family> <property_name> <price> <rent>\n";
	std::cout << "\t4. Add station -> add_station <station_name> <price> <rent>\n";
	std::cout << "\t5. Add facility -> add_facility <facility_name> <price>\n";
	std::cout << "\t6. Add card field -> add_card_field\n";
	std::cout << "\nWhen ready, type start\n";
}

void Monopoly::loadDefualtGame()
{
	addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Brown", 50, 50)));
	addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Light Blue", 50, 50)));
	addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Pink", 100, 100)));
	addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Orange", 100, 100)));
	addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Red", 150, 150)));
	addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Yellow", 150, 150)));
	addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Green", 200, 200)));
	addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily("Dark Blue", 200, 200)));
	/*addFieldFamily(SharedPtr<FieldFamily>(new FieldFamily("Stations")));
	addFieldFamily(SharedPtr<FieldFamily>(new FieldFamily("Facilities")));
	hasFacilities = true;
	hasStations = true;*/

	addProperty("Brown", "Old Kent Road", 60, 80);
	addCardField();
	addProperty("Brown", "Whitechapel Road", 60, 100);
	addCardField();

	addStation("Kings Cross Station", 200, 25);

	addProperty("Light Blue", "The Angel, Islington", 100, 100);
	addCardField();
	addProperty("Light Blue", "Euston Road", 100, 100);
	addProperty("Light Blue", "Pentonville Road", 120, 120);

	addProperty("Pink", "Pall Mall", 120, 120);
	addFacility("Electric Company", 150);
	addProperty("Pink", "Whitehall", 120, 120);
	addProperty("Pink", "Northumberland Avenue", 140, 140);

	addStation("Marylebone Station", 200, 25);

	addProperty("Orange", "Bow Street", 180, 140);
	addCardField();
	addProperty("Orange", "Marlborough Street", 180, 140);
	addProperty("Orange", "Vine Street", 200, 160);

	addProperty("Red", "Strand", 220, 160);
	addCardField();
	addProperty("Red", "Fleet Street", 220, 160);
	addProperty("Red", "Trafalgar Square", 240, 180);

	addStation("Fenchurch St. Station", 200, 25);

	addProperty("Yellow", "Leicester Square", 260, 180);
	addFacility("Water Works", 150);
	addProperty("Yellow", "Coventry Street", 260, 180);
	addProperty("Yellow", "Piccadilly", 280, 200);

	addProperty("Green", "Regent Street", 300, 200);
	addCardField();
	addProperty("Green", "Oxford Street", 300, 200);
	addProperty("Green", "Bond Street", 320, 220);

	addStation("Liverpool Street Station", 200, 25);

	addCardField();
	addProperty("Dark Blue", "Park Lane", 350, 250);
	addCardField();
	addProperty("Dark Blue", "Mayfair", 400, 300);

	fillDeckWithCards();
	//FieldFamily* browns = new PropertyFamily("Brown", 50, 50);
	//FieldFamily* lightBlues = new PropertyFamily("Light Blue", 50, 50);
	//FieldFamily* pinks = new PropertyFamily("Pink", 100, 100);
	//FieldFamily* oranges = new PropertyFamily("Orange", 100, 100);
	//FieldFamily* reds = new PropertyFamily("Red", 150, 150);
	//FieldFamily* yellows = new PropertyFamily("Yellow", 150, 150);
	//FieldFamily* greens = new PropertyFamily("Green", 200, 200);
	//FieldFamily* darkBlues = new PropertyFamily("Dark Blue", 200, 200);
	//FieldFamily* stations = new FieldFamily("Stations");
	//FieldFamily* facilities = new FieldFamily("Facilities");

	//addFieldFamily(SharedPtr<FieldFamily>(browns));
	//addFieldFamily(SharedPtr<FieldFamily>(lightBlues));
	//addFieldFamily(SharedPtr<FieldFamily>(pinks));
	//addFieldFamily(SharedPtr<FieldFamily>(oranges));
	//addFieldFamily(SharedPtr<FieldFamily>(reds));
	//addFieldFamily(SharedPtr<FieldFamily>(yellows));
	//addFieldFamily(SharedPtr<FieldFamily>(greens));
	//addFieldFamily(SharedPtr<FieldFamily>(darkBlues));
	//addFieldFamily(SharedPtr<FieldFamily>(stations));
	//addFieldFamily(SharedPtr<FieldFamily>(facilities));
	//addCardFields(8);
}

bool Monopoly::canStartGame() const
{
	return players.getSize() == playerCount && board->isBoardFull() && !deck->isEmpty();
}

void Monopoly::startGame()
{
	if (!canStartGame())
	{
		MyString message = " You have ";
		message += MyString(playerCount - players.getSize());
		message += " missing players, ";
		message += MyString(board->getMissingFields());
		message += " missing fields and ";
		message += MyString(deck->isEmpty());
		message += " missing cards";
		throw std::runtime_error(message.c_str());
	}

	//randomiseBoard();
	//printBoard();
	Bank::giveInitialBalance(players);
}

void Monopoly::fillDeckWithCards()
{
	deck->addCard(SharedPtr<Card>(new MovePositionCard(3, board->getTotalSize())));
	deck->addCard(SharedPtr<Card>(new PaymentCard(200)));
	deck->addCard(SharedPtr<Card>(new MovePositionCard(-1, board->getTotalSize())));
	deck->addCard(SharedPtr<Card>(new MovePositionCard(2, board->getTotalSize())));
	deck->addCard(SharedPtr<Card>(new PaymentCard(-200)));
	deck->addCard(SharedPtr<Card>(new PaymentCard(300)));
}

void Monopoly::printBoard() const
{
	board->printBoard(players);
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
	board->addCardFields(count, deck);
}

void Monopoly::addPlayer(SharedPtr<Player>& player)
{
	addPlayer(std::move(player));
}

void Monopoly::addPlayer(SharedPtr<Player>&& player)
{
	if (players.getSize() == GameConstants::MAX_PLAYER_COUNT || players.getSize() == playerCount)
		throw std::runtime_error("Max player count reached");

	for (size_t i = 0; i < players.getSize(); i++)
	{
		if (players[i]->compareUsername(player))
			throw std::invalid_argument("There already is a player with this username");
	}
	players.push_back(std::move(player));
}

void Monopoly::addPlayer(const MyString& username)
{
	addPlayer(SharedPtr<Player>(new Player(username)));
}

bool Monopoly::checkUniqueFieldFamilyName(const SharedPtr<FieldFamily>& fieldFamily) const
{
	for (size_t i = 0; i < fieldFamilies.getSize(); i++)
	{
		if (fieldFamilies[i]->comapreName(fieldFamily))
			return false;
	}

	return true;
}

bool Monopoly::canAddFieldFamily(const SharedPtr<FieldFamily>& fieldFamily,
	UniquePtr<Iterator<SharedPtr<BuyableField>>>& mainIterator)
{
	if(!checkUniqueFieldFamilyName(fieldFamily))
		throw std::invalid_argument("There already is a field family with this name");

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

void Monopoly::addFieldFamily(SharedPtr<FieldFamily>& fieldFamily)
{
	addFieldFamily(std::move(fieldFamily));
}

void Monopoly::addFieldFamily(SharedPtr<FieldFamily>&& fieldFamily)
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

		fieldFamilies.push_back(std::move(fieldFamily));
	}
}

void Monopoly::addFieldFamily(const MyString& fieldFamilyName)
{
	addFieldFamily(SharedPtr<FieldFamily>(new FieldFamily(fieldFamilyName)));
}

void Monopoly::addPropertyFamily(const MyString& propertyFamilyName, unsigned cottageCost, unsigned castleCost)
{
	addFieldFamily(SharedPtr<FieldFamily>(new PropertyFamily(propertyFamilyName, cottageCost, castleCost)));
}

void Monopoly::addProperty(const MyString& propertyFamilyName, 
	const MyString& propertyName, unsigned price, unsigned rent)
{
	SharedPtr<FieldFamily> propertyFamily = findFieldFamily(propertyFamilyName);
	Property* ptr = new Property(propertyName, price, rent);

	addField(SharedPtr<Field>(ptr));
	propertyFamily->addField(SharedPtr<BuyableField>(ptr));
}

void Monopoly::addFacility(const MyString& propertyName, unsigned price)
{
	if (!hasFacilities)
		addFieldFamily("Facilities");

	SharedPtr<FieldFamily> facilities = findFieldFamily("Facilities");
	Facility* ptr = new Facility(propertyName, price);

	addField(SharedPtr<Field>(ptr));
	facilities->addField(SharedPtr<BuyableField>(ptr));

	hasFacilities = true;
}

void Monopoly::addStation(const MyString& propertyName, unsigned price, unsigned rent)
{
	if (!hasStations)
		addFieldFamily("Stations");

	SharedPtr<FieldFamily> stations = findFieldFamily("Stations");
	Station* ptr = new Station(propertyName, price, rent);

	addField(SharedPtr<Field>(ptr));
	stations->addField(SharedPtr<BuyableField>(ptr));

	hasStations = true;
}

void Monopoly::addCardField()
{
	addField(SharedPtr<Field>(new CardField(deck)));
}

void Monopoly::addMoveCard(unsigned positions)
{
	deck->addCard(SharedPtr<Card>(new MovePositionCard(positions, board->getTotalSize())));
}

void Monopoly::addPaymentCard(int value)
{
	deck->addCard(SharedPtr<Card>(new PaymentCard(value)));
}

void Monopoly::addField(SharedPtr<Field>& field)
{
	board->addField(field);
}

void Monopoly::addField(SharedPtr<Field>&& field)
{
	board->addField(std::move(field));
}

size_t Monopoly::getPlayerCount() const
{
	return players.getSize();
}

void Monopoly::printPlayersTurnMessage()
{
	//system("cls");
	printBoard();

	std::cout << "Player";
	setColor(players[currentPlayer]->getColor());;
	std::cout << players[currentPlayer]->getUsername();
	resetColor();
	std::cout << "\'s turn\n";
	std::cout << "Balance: " << players[currentPlayer]->getBalance() << '\n';
	
	if (players[currentPlayer]->isInJail())
	{
		if (!getPlayerOutOfJail())
		{
			currentPlayer++;
			currentPlayer %= playerCount;
			
			system("cls");
			printPlayersTurnMessage();
			
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

	SharedPtr<Field>& currentField = (*board)[players[currentPlayer]->getPosition()];
	//currentField->action(players[currentPlayer]);
	fieldActionUntilSuccess(currentField);

	currentPlayer++;
	currentPlayer %= playerCount;
}

void Monopoly::fieldActionUntilSuccess(SharedPtr<Field> currentField)
{
	do
	{
		currentField->printLandingMessage();
		bool canContinue = currentField->action(players[currentPlayer]);
		//players[currentPlayer]->moveWith(0, board->getTotalSize());
		if (canContinue)
			break;

		currentField = (*board)[players[currentPlayer]->getPosition()];

	} while (true);
}

size_t Monopoly::throwDice() const
{
	int firstDice, secondDice;
	srand(time(0));

	firstDice = (rand() % 6) + 1;
	secondDice = (rand() % 6) + 1;

	std::cout << "You threw a " << firstDice << " and a " << secondDice << "\n\n";

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
	std::cout << "\nFormat: build <mortgage_type> <property_name>\n";
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

SharedPtr<FieldFamily>& Monopoly::findFieldFamily(const MyString& familyName)
{
	for (size_t i = 0; i < fieldFamilies.getSize(); i++)
	{
		if (fieldFamilies[i]->comapreName(familyName))
			return fieldFamilies[i];
	}

	throw std::invalid_argument("There isn't a field family with this name");
}
