#include "CantAffordException.h"

CantAffordException::CantAffordException(const char* msg) : message(msg)
{}

const char* CantAffordException::what() const
{
    return message.c_str();
}
