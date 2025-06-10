#include "InputProcessor.h"
#include <iostream>

char InputProcessor::askYesOrNo()
{
	char answer;
	std::cin >> answer;

	while (answer != 'y' && answer != 'n')
	{
		std::cout << "Invalid input! Only valid options are 'y' and 'n'\n";
		std::cout << "Enter input(y|n): ";
		std::cin >> answer;
	}

	return answer;
}
