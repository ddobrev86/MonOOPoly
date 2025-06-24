#include "EndGameException.h"

EndGameException::EndGameException(const SharedPtr<Player>& winner)
{
    this->winner = winner;
}

const char* EndGameException::what() const
{
    MyString message = "Congratulations ";
    message += winner->getUsername();
    message += ". You won!\n";

    return message.c_str();
}
