#include "Id.h"
//isspace(char) will return true if space
//isalpha for if alphabet
//isnum for if number
void Id::S0(const std::string& input)
{
	bool check_digit = true;
	bool check_alpha = false;
	check_alpha = check_for_sign(check_alpha, input[0]);
	std::string mal_input = input;
	if (!isalpha(mal_input[0]) || !check_alpha)
		Serr();
	else
	{

		while (!isspace(mal_input[0]) && (check_digit || check_alpha))//isalpha(mal_input[0] || (isdigit(mal_input[0])))))
		{
			inputRead++;
			mal_input = mal_input.substr(1);
			check_digit = isdigit(mal_input[0]);
			check_alpha = isalpha(mal_input[0]);
			if (check_alpha)
				check_alpha = check_for_sign(check_alpha, mal_input[0]);
		}
	}
}

bool Id::check_for_sign(bool alpha_bool, char current_index)
{
	if (current_index == '(')
		return false;
	if (current_index == ')')
		return false;
	if (current_index == '.')
		return false;
	if (current_index == '*')
		return false;
	if (current_index == '.')
		return false;
	if (current_index == ':')
		return false;
	if (current_index == '?')
		return false;
	if (current_index == '\'')
		return false;

	return true;
}