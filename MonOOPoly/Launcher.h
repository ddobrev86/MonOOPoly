#pragma once
#include "Monopoly.h"

class Launcher
{
public:
	static void run();
	static void startGame(Monopoly* monopoly);
	static void createElements(Monopoly* monopoly);
	static void playGame(Monopoly* monopoly);
};

