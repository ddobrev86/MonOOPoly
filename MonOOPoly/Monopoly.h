#pragma once
#include "MyVector.hpp"
#include "Board.h"
#include "Player.h"
#include "SharedPtr.hpp"

namespace Constants
{
	const size_t MAX_PLAYER_COUNT = 6;
	const size_t MIN_PLAYER_COUNT = 2;
	const size_t STANDART_BOARD_SIZE = 11;
}

class Monopoly
{
private:
	static Monopoly* instance;

	UniquePtr<Board> board;
	MyVector<SharedPtr<Player>> players;
	size_t currentPlayer;
	//size_t playerCount;

	Monopoly(size_t playerCount, size_t boardSize);
public:
	static Monopoly* getInstance(size_t playerCount, size_t boardSize);

	Monopoly(const Monopoly& other) = delete;
	Monopoly& operator=(const Monopoly& other) = delete;
	
	void addPlayer(const SharedPtr<Player>& player);
	void addPlayer(const MyString& username);

	size_t getPlayerCount() const;

	void actPlayerAction();

	bool throwPair() const;
	size_t throwDice() const;
	void movePlayer();

	bool getPlayerOutOfJail();
};

