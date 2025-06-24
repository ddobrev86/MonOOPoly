#pragma once
#include "MyString.h"
#include "UniquePtr.hpp"
#include "SharedPtr.hpp"

enum class Colors
{
	RED = 31,
	GREEN,
	YELLOW,
	BLUE,	
	MAGENTA,
	CYAN
};

class Player
{
private:
	static int nextColor;

	MyString username;
	unsigned balance;
	size_t currentPos;
	bool inJail;
	size_t remainingToRansom;
	Colors color;

public:
	Player(const MyString& username);
	~Player();

	bool compareUsername(const MyString& username);
	bool compareUsername(const UniquePtr<Player>& other);
	bool compareUsername(const SharedPtr<Player>& other);
	void setUsername(const MyString& username);

	const MyString& getUsername() const;

	void moveTo(size_t newPos);
	void moveWith(int positions, size_t boardSize);

	void addToBalance(size_t balanceChange);
	void removeFromBalance(size_t balanceChange);
	void removePercent(double percent);
	bool canAfford(size_t price) const;

	size_t getPosition() const;
	unsigned getBalance() const;

	bool isInJail() const;
	void goToJail();
	void getOutOfJail();

	size_t getRemainingToRansom() const;
	
	int getColor() const;
	void printUsernameInColor() const;
	void lowerRansom();
};

