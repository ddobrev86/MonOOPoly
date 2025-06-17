#pragma once
#include "Monopoly.h"

class Launcher
{
public:
	static void run();
	static void startGame(Monopoly* monopoly, bool& isDefault);
	static void createElements(Monopoly* monopoly, bool isDefault);
	static void playGame(Monopoly* monopoly);
};

