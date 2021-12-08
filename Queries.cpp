#include "Queries.h"

void Queries::S0(const std::string& input)
{
	if (input.size() < 7)
		Serr();
	else if (input.substr(0, 7) == "Queries")
		inputRead = inputRead + 7;
	else
		Serr();
}