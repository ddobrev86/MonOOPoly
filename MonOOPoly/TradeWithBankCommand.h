#pragma once
#include "Command.h"

class TradeWithBankCommand : public Command
{
private:
	SharedPtr<BuyableField> fieldToTrade;
	int& neededAmount;
public:
	TradeWithBankCommand(const SharedPtr<BuyableField>& fieldToTrade, 
		int& neededAmount);

	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

