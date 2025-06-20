#include "utilities.h"
#include <iostream>

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
