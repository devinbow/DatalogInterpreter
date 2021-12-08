#include "Add.h"

void Add::S0(const std::string& input)
{
	if (input[index] == '+')
	{
		inputRead = 1;
	}
	else
		Serr();
}