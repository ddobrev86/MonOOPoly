#pragma once
#include "SharedPtr.hpp"
#include "Player.h"
#include "MyVector.hpp"

class PendingPayment
{
private:
	static MyVector<SharedPtr<Player>> playersToPay;
	static unsigned neededAmount;
	static SharedPtr<Player> payer;
	//static SharedPtr<
public:
	static void pay();
	static void clear();
	static void setPayer(const SharedPtr<Player>& payer);
	static void addReceiver(const SharedPtr<Player>& player);
	static void setNeededAmount(unsigned neededAmount);
};

