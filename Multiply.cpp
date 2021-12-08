#include "Multiply.h"
void Multiply::S0(const std::string& input)
{
	if (input[0] == '*')
	{
		inputRead++;
	}
	else
		Serr();
}