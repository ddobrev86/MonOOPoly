#pragma once
#include "Command.h"

class TradeWithPlayerCommand : public Command
{
private:
	SharedPtr<BuyableField> fieldToTrade;
	int& neededAmount;
public:
	TradeWithPlayerCommand(const SharedPtr<BuyableField>& fieldToTrade,
		int& neededAmount);

	void execute(Monopoly* monopoly) override;
	Command* clone() const override;
};

