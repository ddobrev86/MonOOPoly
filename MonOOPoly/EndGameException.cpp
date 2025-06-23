#include "EndGameException.h"

EndGameException::EndGameException(const SharedPtr<Player>& winner)
{
    this->winner = winner;
}

const char* EndGameException::what() const
{
    MyString message = "Congratulations " + winner->getUsername() + ". You won!";
    return message.c_str();
}
