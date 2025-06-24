#include "GiveUpException.h"

const char* GiveUpException::what() const
{
    return "You lost the game";
}
