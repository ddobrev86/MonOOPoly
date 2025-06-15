#pragma once
#include "SharedPtr.hpp"
#include "Player.h"
#include "BuyableField.h"
#include "Bank.h"
#include "UniquePtr.hpp"

class Trade
{
public:
	static void sellToPlayer(SharedPtr<Player>& sender, 
		SharedPtr<Player>& receiver, SharedPtr<BuyableField>& field);

	static void sellToBank(SharedPtr<Player>& sender , SharedPtr<BuyableField>& field);
};

