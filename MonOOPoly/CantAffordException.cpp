#include "CantAffordException.h"

CantAffordException::CantAffordException(const char* msg, int neededAmount) : message(msg)
{
    this->neededAmount = neededAmount;
}

const char* CantAffordException::what() const
{
    return message.c_str();
}

int CantAffordException::getNeededAmount() const
{
    return neededAmount;
}
