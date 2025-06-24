#include "Player.h"
#include "utilities.h"
#include "Bank.h"

int Player::nextColor = 31;

Player::Player(const MyString& username)
{
    this->username = username;
    balance = 0;
    currentPos = 0;
    inJail = false;

    color = (Colors)(nextColor++);
}

bool Player::compareUsername(const MyString& username)
{
    bool test = (this->username == username);
    return this->username == username;
}

bool Player::compareUsername(const UniquePtr<Player>& other)
{
    return username == other->username;
}

bool Player::compareUsername(const SharedPtr<Player>& other)
{
    bool test = (this->username == username);
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

void Player::moveWith(int positions, size_t boardSize)
{
    if(positions < 0 && currentPos + positions < 0)
    { 
        currentPos = boardSize + currentPos + positions;
        return;
    }

    currentPos += positions;

    if (currentPos >= boardSize)
    {
        currentPos %= boardSize;
        if(currentPos != 0)
            Bank::goTroughStart(this);
    }
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

int Player::getColor() const
{
    return (int)color;
}

void Player::printUsernameInColor() const
{
    setColor((int)color);;
    std::cout << username;
    resetColor();
}

void Player::lowerRansom()
{
    if (remainingToRansom > 0)
        remainingToRansom--;
}
