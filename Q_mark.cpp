#include "Q_mark.h"

void Q_mark::S0(const std::string& input)
{
	if (input[0] == '?')
	{
		inputRead++;
	}
	else
		Serr();
}