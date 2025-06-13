#include "utilities.h"

unsigned twoToPower(unsigned power)
{
	unsigned result = 1;
	result <<= power;

	return result;
}