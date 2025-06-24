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

Player::~Player()
{
    nextColor--;
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
    {
        MyString errorMessage = "\n" + username + ", you don't have enough money to continue with this action!";
        throw std::invalid_argument(errorMessage.c_str());
    }
        
    
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

void Player::goToJail(size_t jailPos)
{
    remainingToRansom = 2;
    inJail = true;
    moveTo(jailPos);
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

void Player::readFromFile(std::ifstream& ifs)
{
    if (!ifs.is_open())
        return;

    int colorAsInt;

    username.readFromFile(ifs);
    ifs.read((char*)&balance, sizeof(unsigned));
    ifs.read((char*)&currentPos, sizeof(size_t));
    ifs.read((char*)&inJail, sizeof(bool));
    ifs.read((char*)&remainingToRansom, sizeof(size_t));
    ifs.read((char*)&colorAsInt, sizeof(int));

    this->color = (Colors)colorAsInt;
}

void Player::saveToFile(std::ofstream& ofs) const
{
    if (!ofs.is_open())
        return;

    int colorAsInt = (int)color;

    username.saveToFile(ofs);
    ofs.write((const char*)&balance, sizeof(unsigned));
    ofs.write((const char*)&currentPos, sizeof(size_t));
    ofs.write((const char*)&inJail, sizeof(bool));
    ofs.write((const char*)&remainingToRansom, sizeof(size_t));
    ofs.write((const char*)&colorAsInt, sizeof(int));
}
