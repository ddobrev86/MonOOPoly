#pragma once
#include "SharedPtr.hpp"
#include "UniquePtr.hpp"
#include "Player.h"
#include "BuyableField.h"
#include "Bank.h"

class Trade
{
public:
	static void sellToPlayer(SharedPtr<Player>& receiver, 
		SharedPtr<BuyableField>& field, int& neededAmount);

	static void sellToBank(SharedPtr<BuyableField>& field, int& neededAmount);
};

