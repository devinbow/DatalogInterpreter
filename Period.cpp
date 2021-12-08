#include "Period.h"

void Period::S0(const std::string& input)
{
	if (input[0] == '.')
		inputRead++;
	else
		Serr();
}