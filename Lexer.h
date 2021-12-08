#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"
//where the magic happens
class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    Automaton* maxAutomata;

    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();

    void Run(std::string& input);

    void toString() { for (Token* each_token : tokens) each_token->ToString(each_token->getType(), each_token->getDescription(), each_token->getLine_s()); }
    
    // TODO: add other public methods here

	bool check_for_sign(char current_index)
	{
		if (current_index == '(')
			return true;
		if (current_index == ')')
			return true;
		if (current_index == '.')
			return true;
		if (current_index == '*')
			return true;
		if (current_index == '.')
			return true;
		if (current_index == ':')
			return true;
		if (current_index == '?')
			return true;
		if (current_index == '\'')
			return true;

		return false;
	}

	bool is_not_alpha_check(char current_index)
	{
		if (isspace(current_index))
			return true;
		if (check_for_sign(current_index))
		{
			return true;
		}
		return false;
	}

	std::vector<Token*> getTokenList()
	{
		return tokens;
	}

	std::vector<Automaton*> getAutomataList()
	{
		return automata;
	}

};
#endif // LEXER_H