#pragma once
#include "MyString.h"
#include "UniquePtr.hpp"
#include "SharedPtr.hpp"

class Player
{
private:
	MyString username;
	unsigned balance;
	size_t currentPos;
	bool inJail;
	size_t remainingToRansom;

public:
	Player(const MyString& username);

	bool compareUsername(const MyString& username);
	bool compareUsername(const UniquePtr<Player>& other);
	bool compareUsername(const SharedPtr<Player>& other);
	void setUsername(const MyString& username);

	const MyString& getUsername() const;

	void moveTo(size_t newPos);
	void moveWith(size_t positions, size_t boardSize);

	void addToBalance(size_t balanceChange);
	void removeFromBalance(size_t balanceChange);
	bool canAfford(size_t price);

	size_t getPosition() const;
	unsigned getBalance() const;

	bool isInJail() const;
	void goToJail();
	void getOutOfJail();

	size_t getRemainingToRansom() const;
};

