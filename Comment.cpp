#include "Comment.h"

void Comment::S0(const std::string& input)
{
	bool closed_comment = false;
	std::string new_input = input;
	if (new_input[index] == '#')
	{
		if (new_input[index + 1] == '|')
		{
			/*if (input.substr(input.size() - 2, input.size()) != "|#")
			{
				Serr(); CHANGE THIS
			}*/
				while (!new_input.empty() && (new_input[index] != '|' || new_input[index + 1] != '#'))
				{
					inputRead++;
					if (new_input[0] == '\n')
					{
						if (!empty(new_input.substr(1)))
							newLines++;
					}
					new_input = new_input.substr(1);
					if (new_input.size() > 1 && (new_input[index] == '|' && new_input[index + 1] == '#'))
					{
						closed_comment = true;
					}

				}
				if (!closed_comment)
				{
					this->type = TokenType::UNDEFINED;
				}
				else if (!new_input.empty())
				{
					inputRead = inputRead + 2;
					new_input = new_input.substr(2);
				}
				else
					Serr();

		}
		else
		{
			while (new_input[index] != '\n')
			{
				inputRead++;
				new_input = new_input.substr(1);
			}
		}
	}
	else
		Serr();
}