#pragma once
#include "Monopoly.h"

class Launcher
{
private:
	static void startGame(Monopoly* monopoly, bool& isDefault);
	static void createElements(Monopoly* monopoly, bool isDefault);
	static void playGame(Monopoly* monopoly);
	static void trade(Monopoly* monopoly, SharedPtr<BuyableField>& fieldToTrade,
		int& neededAmount);

	static void printFieldsToTradeMessage(const MyVector<SharedPtr<BuyableField>>& ownedFields,
		int neededAmount);
	static void obligatoryTrade(Monopoly* monopoly, int neededAmount);

	static void printGameTypeOptions();
	static void printDefaultCreateElementsCommands();
	static void printManualCreateElementsCommands();
public:
	static void run();
	static void build(Monopoly* monopoly);

};

