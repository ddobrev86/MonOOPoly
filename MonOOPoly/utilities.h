#pragma once

unsigned twoToPower(unsigned power);
size_t digitCount(unsigned num);
char digitToChar(unsigned digit);
void reverse(char* str, size_t size);
unsigned absoluteValue(int num);
void printTaxingMessage();
void removeLeadingSpaces(char* str);

void setColor(int textColor);

void resetColor();

namespace GameConstants
{
	const size_t MAX_PLAYER_COUNT = 6;
	const size_t MIN_PLAYER_COUNT = 2;
	const size_t STANDART_BOARD_SIZE = 11;
}

namespace MortgageConstants
{
	static const double COTTAGE_RENT_INCREASE = 0.15;
	static const double CASTLE_RENT_INCREASE = 0.5;
}