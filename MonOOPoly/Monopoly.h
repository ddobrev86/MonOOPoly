#pragma once
#include "MyVector.hpp"
#include "SharedPtr.hpp"
#include "Board.h"
#include "Player.h"
#include "FieldFamily.h"
#include "PropertyFamily.h"
#include "utilities.h"
#include "CardField.h"
#include "CardDeck.h"
#include "MovePositionCard.h"
#include "PaymentCard.h"
#include "GroupPaymentCard.h"

class Monopoly
{
private:
	static Monopoly* instance;

	UniquePtr<Board> board;
	MyVector<SharedPtr<Player>> players;
	size_t currentPlayer;
	MyVector<SharedPtr<FieldFamily>> fieldFamilies;
	size_t playerCount;
	SharedPtr<CardDeck> deck;

	bool hasStations;
	bool hasFacilities;
	size_t jailPos;

	Monopoly(size_t playerCount, size_t boardSize);
public:
	static Monopoly* getInstance(size_t playerCount, size_t boardSize);
	static Monopoly* getInstance();
	
	void goToNextPlayer();

	void loadDefualtGame();
	bool canStartGame() const;
	void startGame();

	void fillDeckWithCards();

	Monopoly(const Monopoly& other) = delete;
	Monopoly& operator=(const Monopoly& other) = delete;
	
	void printBoard() const;
	void randomiseBoard();

	void switchFields(size_t firstIndex, size_t secondIndex);
	void addCardFields(size_t count);

	void addPlayer(SharedPtr<Player>& player);
	void addPlayer(SharedPtr<Player>&& player);
	void addPlayer(const MyString& username);

	bool checkUniqueFieldFamilyName(const SharedPtr<FieldFamily>& fieldFamily) const;
	bool canAddFieldFamily(const SharedPtr<FieldFamily>& fieldFamily,
		UniquePtr<Iterator<SharedPtr<BuyableField>>>& mainIterator);

	void addFieldFamily(SharedPtr<FieldFamily>& fieldFamily);
	void addFieldFamily(SharedPtr<FieldFamily>&& fieldFamily);

	void addFieldFamily(const MyString& fieldFamilyName);
	void addPropertyFamily(const MyString& propertyFamilyName, 
		unsigned cottageCost, unsigned castleCost);

	void addField(SharedPtr<Field>& field);
	void addField(SharedPtr<Field>&& field);

	void addProperty(const MyString& propertyFamilyName,
		const MyString& propertyName, unsigned price, unsigned rent);
	void addFacility(const MyString& propertyName, unsigned price);
	void addStation(const MyString& propertyName, unsigned price, unsigned rent);

	void addCardField();

	void addMoveCard(unsigned positions);
	void addPaymentCard(int value);
	void addGroupPaymentCard(int value);

	size_t getPlayerCount() const;

	void printPlayersTurnMessage();
	void fieldActionUntilSuccess(SharedPtr<Field> currentField);
	
	void actPlayerThrowDiceCommand();
	void actBuyMortgageCommand();
	void actBuildCommand(const MyString& propertyName, 
		const MyString& mortgageType, MyVector<SharedPtr<FieldFamily>>& validFamilies);
	void printOwnershipMap() const;

	bool canBuild() const;
	void findValidFamilies(MyVector<SharedPtr<FieldFamily>>& validFamilies);
	void printValidFamiliesMessage(const MyVector<SharedPtr<FieldFamily>>& validFamilies) const;

	bool throwPair() const;
	size_t throwDice(bool& isPair, unsigned& pairCount) const;
	void movePlayer(bool& isPair, unsigned& pairCount);

	bool getPlayerOutOfJail();

	void tradeBetweenPlayers(const MyString& receiverName,
		SharedPtr<BuyableField>& field, int& neededAmount);
	void tradeWithBank(SharedPtr<BuyableField>& field, int& neededAmount);

	SharedPtr<BuyableField>& findBuyableField(const MyVector<SharedPtr<FieldFamily>>& families,
		const MyString& propertyName);
	SharedPtr<Player>& findPlayer(const MyString& playerName);

	SharedPtr<FieldFamily>& findFieldFamily(const MyString& familyName);
	void findOwnedFields(MyVector<SharedPtr<BuyableField>>& ownedFields) const;

	void playerExitGame();
	void printPlayersThatCanAfford(unsigned amount) const;
};

