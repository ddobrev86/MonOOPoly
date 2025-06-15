#include "TradeWithPlayerCommand.h"

void TradeWithPlayerCommand::execute(Monopoly* monopoly) const
{
    MyString receiverName, propertyName;
    std::cin >> receiverName >> propertyName;
    
    monopoly->tradeBetweenPlayers(receiverName, propertyName);
}

Command* TradeWithPlayerCommand::clone() const
{
    return new TradeWithPlayerCommand(*this);
}
