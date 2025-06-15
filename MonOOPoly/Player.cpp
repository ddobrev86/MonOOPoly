#include "Player.h"

Player::Player(const MyString& username)
{
    this->username = username;
    balance = 0;
    currentPos = 0;
    inJail = false;
}

bool Player::compareUsername(const MyString& username)
{
    return this->username == username;
}

bool Player::compareUsername(const UniquePtr<Player>& other)
{
    return username == other->username;
}

bool Player::compareUsername(const SharedPtr<Player>& other)
{
    return username == other->username;
}

const MyString& Player::getUsername() const
{
    return username;
}

void Player::moveTo(size_t newPos)
{
    currentPos = newPos;
}

void Player::moveWith(size_t positions, size_t boardSize)
{
    currentPos += positions;
    currentPos %= boardSize;
}

void Player::addToBalance(size_t balanceChange)
{
    balance += balanceChange;
}

void Player::removeFromBalance(size_t balanceChange)
{
    //TODO: add validation if balanceChange is smaller than balance 
    if (!canAfford(balanceChange))
        throw std::invalid_argument("You don't have enough money to continue with this action!");
    
    balance -= balanceChange;
}

void Player::removePercent(double percent)
{
    unsigned toRemove = percent * balance;
    balance -= toRemove;
}

bool Player::canAfford(size_t price) const
{
    return balance >= price;
}

size_t Player::getPosition() const
{
    return currentPos;
}

unsigned Player::getBalance() const
{
    return balance;
}

bool Player::isInJail() const
{
    return inJail;
}

void Player::goToJail()
{
    remainingToRansom = 2;
    inJail = true;
}

void Player::getOutOfJail()
{
    inJail = false;
    remainingToRansom = false;
}

size_t Player::getRemainingToRansom() const
{
    return remainingToRansom;
}
