#pragma once
#include "MyString.h"

class Player
{
private:
	MyString username;
	unsigned balance;
	size_t currentPos;

public:
	Player(const MyString& username);

	bool compareUsername(const MyString& username);
	void setUsername(const MyString& username);

	void moveTo(size_t newPos);

	void addToBalance(size_t balanceChange);
	void removeFromBalance(size_t balanceChange);

	size_t getPosition() const;
};

