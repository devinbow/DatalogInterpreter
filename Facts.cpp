#include "Facts.h"

void Facts::S0(const std::string& input)
{
	if (input.size() < 5)
		Serr();
	else if (input.substr(0, 5) == "Facts")
		inputRead = inputRead + 5;
	else
		Serr();
}