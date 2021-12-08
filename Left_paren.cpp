#include "Left_paren.h"
void Left_paren::S0(const std::string& input)
{
	if (input[0] == '(')
		inputRead++;
	else
		Serr();
}