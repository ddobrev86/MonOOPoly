#pragma once
#include "SharedPtr.hpp"
#include "UniquePtr.hpp"
#include "Player.h"
#include "BuyableField.h"
#include "Bank.h"

class Trade
{
public:
	static void sellToPlayer(SharedPtr<Player>& sender, 
		SharedPtr<Player>& receiver, SharedPtr<BuyableField>& field);

	static void sellToBank(SharedPtr<Player>& sender , SharedPtr<BuyableField>& field);
};

