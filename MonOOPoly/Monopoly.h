#pragma once
#include "MyVector.hpp"
#include "Board.h"
#include "Player.h"
#include "SharedPtr.hpp"
#include "PropertyFamily.h"
#include "FieldFamily.h"
#include "utilities.h"
#include "CardField.h"

class Monopoly
{
private:
	static Monopoly* instance;

	UniquePtr<Board> board;
	MyVector<SharedPtr<Player>> players;
	size_t currentPlayer;
	MyVector<SharedPtr<FieldFamily>> fieldFamilies;
	//size_t playerCount;

	Monopoly(size_t playerCount, size_t boardSize);
public:
	static Monopoly* getInstance(size_t playerCount, size_t boardSize);
	static Monopoly* getInstance();
	static void printGameTypeOptions();

	void loadDefualtGame();

	Monopoly(const Monopoly& other) = delete;
	Monopoly& operator=(const Monopoly& other) = delete;
	
	void printBoard() const;
	void randomiseBoard();

	void switchFields(size_t firstIndex, size_t secondIndex);
	void addCardFields(size_t count);

	void addPlayer(const SharedPtr<Player>& player);
	void addPlayer(const MyString& username);

	bool canAddFieldFamily(const SharedPtr<FieldFamily>& fieldFamily,
		UniquePtr<Iterator<SharedPtr<BuyableField>>>& mainIterator);
	void addFieldFamily(const SharedPtr<FieldFamily>& fieldFamily);
	void addField(const SharedPtr<Field>& field);

	size_t getPlayerCount() const;

	void printPlayersTurnMessage();
	void fieldActionUntilSuccess(SharedPtr<Field>& currentField);
	
	void actPlayerThrowDiceCommand();
	void actBuyMortgageCommand();
	void actBuildCommand(const MyString& propertyName, const MyString& mortgageType);

	void findValidFamilies(MyVector<SharedPtr<FieldFamily>>& validFamilies,
		bool& canBuy);
	void printValidFamiliesMessage(const MyVector<SharedPtr<FieldFamily>>& validFamilies) const;

	bool throwPair() const;
	size_t throwDice() const;
	void movePlayer();

	bool getPlayerOutOfJail();

	void tradeBetweenPlayers(const MyString& receiverName,
		const MyString& propertyName);
	void tradeWithBank(const MyString& propertyName);

	SharedPtr<BuyableField>& findBuyableField(const MyVector<SharedPtr<FieldFamily>>& families,
		const MyString& propertyName);
	SharedPtr<Player>& findPlayer(const MyString& playerName);
};

