#include "String.h"

void String::S0(const std::string& input)
{
	bool double_mark = true;
	//bool apostrophe_check = false;
	std::string temp_input = input;
	//checks if the input is a string right off the bat
	//if (temp_input[0] == '\'' && temp_input[1] == '\'')
	//	inputRead = inputRead + 2;
	//checks if there is even a beginning apostrophe for string
    if (temp_input[0] != '\'')
	{ 
			Serr();
	}
	else
	{
		inputRead++;
		temp_input = temp_input.substr(1);
		do
		{
			//checks for if there is a double apostrophe. If not, then we end the loop at the while condition. 
			//IF PROBLEM WITH STRING LINE, COME BACK HERE
			while (temp_input[0] == '\n')
			{
				if (!empty(temp_input.substr(1)))
				{
					inputRead++;
					newLines++;
					temp_input = temp_input.substr(1);
				}
				else
					temp_input = temp_input.substr(1);
			}
			if (temp_input[0] == '\'')
			{
				if (temp_input[1] != '\'' )//&& !empty(temp_input.substr(2)))
				{
					double_mark = false;
				}
				else
				{
					inputRead++;
					temp_input = temp_input.substr(1);
				}
			}
			if (!empty(temp_input))
			{
				inputRead++;
				temp_input = temp_input.substr(1);
			}
		}
		while (!temp_input.empty() && double_mark);

		//Double mark will only be true if the string continues. If it is true and the input continues, then that means that there was no closing apostrophe. 
		if (double_mark && temp_input.empty())
			this->type = TokenType::UNDEFINED;
		/*
		do
		{
			// there is not always an apostrophe. 
			double_mark = false;
			apost_found = false;
			inputRead++;
			temp_input = temp_input.substr(1);
			if (temp_input[index] == '\'')
			{
				apost_found = true;
				if (temp_input[index + 1] == '\'')
				{
					double_mark = false;
					apost_found = false;
					inputRead++;
					temp_input = temp_input.substr(1);
					inputRead++;
					temp_input = temp_input.substr(1);
				}
			}
			if (temp_input[0] == '\n')
			{
				if (!empty(temp_input.substr(1)))
					newLines++;
				else
					temp_input = temp_input.substr(1);
				//Want to continue when there is a double quote, but not an apostrophe. 
			}
		} while (!temp_input.empty() && (!apost_found && !double_mark));
		if (!temp_input.empty())
		{
			inputRead = inputRead + 1;
			temp_input = temp_input.substr(1);
		}
		else
			if (temp_input.empty())
			{
				this->type = TokenType::UNDEFINED;
			}
			else
				Serr();
		*/
	}
}

//void String::Serr()
//{
	//TokenType undef = TokenType::EOF_TYPE;
//}