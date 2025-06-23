#include "TradingCommandFactory.h"
#include "TradeWithBankCommand.h"
#include "TradeWithPlayerCommand.h"

Command* TradingCommandFactory::createCommand(const MyString& command, 
    SharedPtr<BuyableField>& fieldToTrade, int& neededAmount)
{
    if (command == "trade_with_bank")
        return new TradeWithBankCommand(fieldToTrade, neededAmount);
    else if (command == "trade_with_player")
        return new TradeWithPlayerCommand(fieldToTrade, neededAmount);

    return nullptr;
}
