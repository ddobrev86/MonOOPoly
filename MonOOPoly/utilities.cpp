#include "utilities.h"
#include <iostream>
#pragma warning (disable:4996)

void setColor(int textColor)
{
	std::cout << "\033[" << textColor << "m";
}

void resetColor() 
{ 
	std::cout << "\033[0m"; 
}

unsigned twoToPower(unsigned power)
{
	unsigned result = 1;
	result <<= power;

	return result;
}

size_t digitCount(unsigned num)
{
	if (num == 0)
		return 1;

	size_t count = 0;
	while (num)
	{
		count++;
		num /= 10;
	}
	return count;
}

char digitToChar(unsigned digit)
{
	return digit + '0';
}

void reverse(char* str, size_t size)
{
	size_t end = size / 2;

	for (size_t i = 0; i < end; i++)
		std::swap(str[i], str[size - i - 1]);
}

unsigned absoluteValue(int num)
{
	return (num > 0 ? num : -num);
}

void printTaxingMessage()
{
	setColor(90);
	std::cout << "You have been taxed\n";
	resetColor();
}

void removeLeadingSpaces(char* str)
{
	size_t spacesCount = 0;
	size_t idx = 0, cpyIdx = 0;
	while (str[idx] == ' ')
	{
		spacesCount++;
		idx++;
	}

	if (spacesCount == 0)
		return;

	char* strCopy = new char[strlen(str) + 1];
	strcpy(strCopy, str);
	cpyIdx += spacesCount;

	idx = 0;
	while (strCopy[cpyIdx])
	{
		str[idx] = strCopy[cpyIdx];
		idx++;
		cpyIdx++;
	}

	str[idx] = '\0';

	delete[] strCopy;
}
