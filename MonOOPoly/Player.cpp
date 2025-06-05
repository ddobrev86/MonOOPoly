#include "Player.h"

Player::Player(const MyString& username)
{
    this->username = username;
    balance = 0;
    currentPos = 0;
}

bool Player::compareUsername(const MyString& username)
{
    return this->username == username;
}

void Player::moveTo(size_t newPos)
{
    currentPos = newPos;
}

void Player::addToBalance(size_t balanceChange)
{
    balance += balanceChange;
}

void Player::removeFromBalance(size_t balanceChange)
{
    //TODO: add validation if balanceChange is smaller than balance 

    balance -= balanceChange;
}

size_t Player::getPosition() const
{
    return currentPos;
}
