#include "TradeWithPlayerCommand.h"

TradeWithPlayerCommand::TradeWithPlayerCommand(const SharedPtr<BuyableField>& fieldToTrade,
    int& neededAmount) : neededAmount(neededAmount)
{
    this->fieldToTrade = fieldToTrade;
    //this->neededAmount = neededAmount;
}

void TradeWithPlayerCommand::execute(Monopoly* monopoly)
{
    MyString receiverName;
    receiverName.readLong();
    
    monopoly->tradeBetweenPlayers(receiverName, fieldToTrade, neededAmount);
}

Command* TradeWithPlayerCommand::clone() const
{
    return new TradeWithPlayerCommand(*this);
}
