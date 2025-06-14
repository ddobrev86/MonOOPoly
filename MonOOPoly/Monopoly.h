#pragma once
#include "MyVector.hpp"
#include "Board.h"
#include "Player.h"
#include "SharedPtr.hpp"
#include "PropertyFamily.h"
#include "FieldFamily.h"
#include "utilities.h"

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

	Monopoly(const Monopoly& other) = delete;
	Monopoly& operator=(const Monopoly& other) = delete;
	
	void printBoard() const;

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
};

