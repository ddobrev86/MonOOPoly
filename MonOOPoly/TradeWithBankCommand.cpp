#include "TradeWithBankCommand.h"

void TradeWithBankCommand::execute(Monopoly* monopoly) const
{
    MyString propertyName;
    std::cin >> propertyName;

    monopoly->tradeWithBank(propertyName);
}

Command* TradeWithBankCommand::clone() const
{
    return nullptr;
}
