#include "Right_paren.h"

void Right_paren::S0(const std::string& input)
{
	if (input[0] == ')')
		inputRead++;
	else
		Serr();
}