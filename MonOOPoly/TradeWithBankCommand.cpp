#include "TradeWithBankCommand.h"

TradeWithBankCommand::TradeWithBankCommand(const SharedPtr<BuyableField>& fieldToTrade,
    int& neededAmount) : neededAmount(neededAmount)
{
    this->fieldToTrade = fieldToTrade;
    //this->neededAmount = neededAmount;
}

void TradeWithBankCommand::execute(Monopoly* monopoly)
{
    monopoly->tradeWithBank(fieldToTrade, neededAmount);
}

Command* TradeWithBankCommand::clone() const
{
    return nullptr;
}
