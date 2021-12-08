#include "Rules.h"

void Rules::S0(const std::string& input)
{
	if (input.size() < 5)
		Serr();
	else if (input.substr(0, 5) == "Rules")
		inputRead = inputRead + 5;
	else
		Serr();
}