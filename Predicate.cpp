#include "Predicate.h"
#include <iostream>
void Predicate::parseScheme(std::vector<Token*>& tokens, std::vector<Predicate> &schemeList)
{
	//tokens[5] should be idList
	try
	{
		do
		{
			int calc_scheme = 0;
			if (tokens[calc_scheme]->getType() == TokenType::ID)
			{
				calc_scheme++;
				if (tokens[calc_scheme]->getType() == TokenType::LEFT_PAREN)
				{
					calc_scheme++;
					if (tokens[calc_scheme]->getType() == TokenType::ID)
					{
						calc_scheme++;
						if (tokens[calc_scheme]->getType() != TokenType::COMMA)
						{
							if (tokens[calc_scheme]->getType() != TokenType::RIGHT_PAREN)
							{
								throw(tokens[calc_scheme]);
							}
						}
					}
					else
					{
						throw(tokens[calc_scheme]);
					}
				}
				else
				{
					throw(tokens[calc_scheme]);
				}
			}
			else
			{
				throw(tokens[calc_scheme]);
			}
			//EXPERIMENT: MAKING CALC_SCHEME +3 NOW. NOT SURE IF WILL WORK.
			int initial_calc_scheme = calc_scheme;
			if (tokens[calc_scheme]->getType() != TokenType::RIGHT_PAREN)
			{
				IDList(tokens, calc_scheme);
			}
			std::vector<Parameter> para_list;
			if (tokens.empty())
				return;
			Parameter param = Parameter(tokens[2]->getDescription());
				para_list.push_back(param);

				//The plus one is to move from initial comma to the first ID in list
				for (int i = initial_calc_scheme + 1; i < calc_scheme; i = i + 2)
				{
					param = Parameter(tokens[i]->getDescription());
					para_list.push_back(param);
				}
				//EXPERIMENT: USING STATIC NUMERAL FOR INITIALIZATION
				Predicate temp_pred = Predicate(tokens[0]->getDescription(), para_list);
				schemeList.push_back(temp_pred);
				//+1 is to move from right paren to next scheme
				tokens.erase(tokens.begin(), tokens.begin() + calc_scheme + 1);
		} while (tokens[0]->getType() == TokenType::ID );
	}
	catch (Token* error_token)
	{
		std::cout << "Failure!\n  (" << error_token->tokenToString(error_token->getType()) << ",\"" << error_token->getDescription() << "\"," << error_token->getLine_s() << ")";
		tokens.clear();
		return;
	}
}
	//}
	//catch (Token *current_index)
//	{

	//}
void Predicate::IDList(std::vector<Token*>& tokens, int& current_index)
{
	try {
		do
		{
			if (tokens[current_index]->getType() == TokenType::COMMA)
			{
				if (tokens[current_index + 1]->getType() == TokenType::ID)
				{
					current_index = current_index + 2;
				}
				else
				{
					throw(tokens[current_index+1]);
				}
			}
			else
			{
				throw(tokens[current_index]);
			}
		} while (tokens[current_index]->getType() != TokenType::RIGHT_PAREN);
	}
	catch (Token* error_token)
	{
		std::cout << "Failure!\n  (" << error_token->tokenToString(error_token->getType()) << ",\"" << error_token->getDescription() << "\"," << error_token->getLine_s() << ")";
		tokens.clear();
		return;
	}
}

void Predicate::stringList(std::vector<Token*> &tokens, int& current_index)
{
	try {
		while (tokens[current_index]->getType() != TokenType::RIGHT_PAREN)
		{
			if (tokens[current_index]->getType() == TokenType::COMMA)
			{
				if (tokens[current_index + 1]->getType() == TokenType::STRING)
				{
					current_index = current_index + 2;
				}
				else
				{
					throw(tokens[current_index+1]);
				}
			}
			else
			{
				throw(tokens[current_index]);
			}
		} 
		//EXPERIMENT: WILL NEED TRY-CATCH BLOCK HERE INSTEAD OF IF
	}
	catch (Token* error_token)
	{
		std::cout << "Failure!\n  (" << error_token->tokenToString(error_token->getType()) << ",\"" << error_token->getDescription() << "\"," << error_token->getLine_s() << ")";
		tokens.clear();
		return;
	}
}
void Predicate::parseFacts(std::vector<Token*>& tokens, std::vector<Predicate>& factList)
{
	try
	{
		do
		{
			int calc_fact = 0;
			if (tokens[calc_fact]->getType() == TokenType::ID)
			{
				calc_fact++;
				if (tokens[calc_fact]->getType() == TokenType::LEFT_PAREN)
				{
					calc_fact++;
					if (tokens[calc_fact]->getType() == TokenType::STRING)
					{
						calc_fact++;
						if (tokens[calc_fact]->getType() != TokenType::COMMA)
						{
							if (tokens[calc_fact]->getType() != TokenType::RIGHT_PAREN)
							{
								throw(tokens[calc_fact]);
							}
						}
					}
					else
					{
						throw(tokens[calc_fact]);
					}
				}
				else
				{
					throw(tokens[calc_fact]);
				}
			}
			else
			{
				throw(tokens[calc_fact]);
			}

			int initial_calc_scheme = calc_fact;
			stringList(tokens, calc_fact);
			if (tokens.empty())
				return;
			std::vector<Parameter> para_list;

			Parameter param = Parameter(tokens[2]->getDescription());
			para_list.push_back(param);

			//The plus one is to move from initial comma to the first ID in list
			for (int i = initial_calc_scheme + 1; i < calc_fact; i = i + 2)
			{
				param = Parameter(tokens[i]->getDescription());
				para_list.push_back(param);
			}
			//EXPERIMENT: USING STATIC NUMERAL FOR INITIALIZATION
			Predicate temp_pred = Predicate(tokens[0]->getDescription(), para_list);
			factList.push_back(temp_pred);
			//+1 is to move from right paren to next scheme
			tokens.erase(tokens.begin(), tokens.begin() + calc_fact + 2);
		} while (tokens[0]->getType() == TokenType::ID);
	}
	catch (Token* error_token)
	{
		std::cout << "Failure!\n  (" << error_token->tokenToString(error_token->getType()) << ",\"" << error_token->getDescription() << "\"," << error_token->getLine_s() << ")";
		tokens.clear();
		return;
	}
}
void Predicate::parseQueries(std::vector<Token*>& tokens, std::vector<Predicate>& querieList)
{
	do
	{
		int current_index = 0;
		predicateParse(tokens, current_index, querieList);

	} while (!tokens.empty() && tokens[0]->getType() == TokenType::ID);
}

void Predicate::predicateParse(std::vector<Token*>& tokens, int& current_index, std::vector<Predicate>& querieList)
{
	try
	{
		int initial_current_index = current_index;
		std::vector<Parameter> tempBodyParameter;
		if (tokens[current_index]->getType() == TokenType::ID)
		{
			if (tokens[current_index + 1]->getType() == TokenType::LEFT_PAREN)
			{
				current_index = current_index + 2;
				parameter(tokens, current_index, tempBodyParameter);
				if (tokens.empty())
					return;
				Predicate temp_pred = Predicate(tokens[initial_current_index]->getDescription(), tempBodyParameter);
				querieList.push_back(temp_pred);
				tokens.erase(tokens.begin(), tokens.begin() + current_index);
				current_index = 0;
				if (tokens[current_index]->getType() != TokenType::Q_MARK)
				{
					throw(tokens[current_index]);
				}
				tokens.erase(tokens.begin());
				return;
			}
			else
			{
				throw(tokens[current_index]);
			}
		}
		else
		{
			throw(tokens[current_index]);
		}
	}
	catch (Token* error_token)
	{
		std::cout << "Failure!\n  (" << error_token->tokenToString(error_token->getType()) << ",\"" << error_token->getDescription() << "\"," << error_token->getLine_s() << ")";
		tokens.clear();
		return;
	}
}

void Predicate::parameter(std::vector<Token*> &tokens, int& current_index, std::vector<Parameter>& tempBodyParameter)
{
	try
	{
		if (tokens[current_index]->getType() == TokenType::STRING) //|| tokens[current_index]->getType() == TokenType::ID)
		{
			Parameter temp_pred = Parameter(tokens[current_index]->getDescription(), "STRING");
			tempBodyParameter.push_back(temp_pred);
			current_index++;
			parameterList(tokens, current_index, tempBodyParameter);
			return;
		}
		else if (tokens[current_index]->getType() == TokenType::ID)
		{
			Parameter temp_pred = Parameter(tokens[current_index]->getDescription(), "ID");
			tempBodyParameter.push_back(temp_pred);
			current_index++;
			parameterList(tokens, current_index, tempBodyParameter);
			return;
		}
		else
		{
			throw(tokens[current_index]);
		}
	}
	catch (Token* error_token)
	{
		std::cout << "Failure!\n  (" << error_token->tokenToString(error_token->getType()) << ",\"" << error_token->getDescription() << "\"," << error_token->getLine_s() << ")";
		tokens.clear();
		return;
	}
}

void Predicate::parameterList(std::vector<Token*> &tokens, int& current_index, std::vector<Parameter>& tempBodyParameter)
{
	try
	{
		if (tokens[current_index]->getType() == TokenType::COMMA)
		{
			current_index++;
			parameter(tokens, current_index, tempBodyParameter);
			if (tokens.empty())
				return;
		}
		else if (tokens[current_index]->getType() == TokenType::RIGHT_PAREN)
		{
			current_index++;
			return;
		}
		else
		{
			throw(tokens[current_index]);
		}
	}
	catch (Token* error_token)
	{
		std::cout << "Failure!\n  (" << error_token->tokenToString(error_token->getType()) << ",\"" << error_token->getDescription() << "\"," << error_token->getLine_s() << ")";
		tokens.clear();
		return;
	}
}

void Predicate::schemeToString(std::vector<Predicate> & schemeList)
{
	std::cout << "Success!" << std::endl << "Schemes(" << schemeList.size() << "):\n";
	for (size_t i = 0; i < schemeList.size(); i++)
	{
		std::cout << "  " << schemeList[i].ID << "(";
		std::cout << schemeList[i].para_list[0].Parameter::getContent();
		for(size_t j = 1 ; j < schemeList[i].para_list.size() ; j++)
			std::cout << "," << schemeList[i].para_list[j].Parameter::getContent();
		std::cout << ")" << std::endl;
	}
}


void Predicate::factToString(std::vector<Predicate> & factsList, std::set<std::string>& domain_list)
{
	std::cout << "Facts(" << factsList.size() << "):\n";
	for (size_t i = 0; i < factsList.size(); i++)
	{
		std::cout << "  " << factsList[i].ID << "(";
		std::cout << factsList[i].para_list[0].Parameter::getContent();
		for (size_t j = 1; j < factsList[i].para_list.size(); j++)
			std::cout << "," << factsList[i].para_list[j].Parameter::getContent();		
		for (size_t j = 0; j < factsList[i].para_list.size(); j++)
			domain_list.insert(factsList[i].para_list[j].Parameter::getContent());

		std::cout << ")." << std::endl;
	}
}

void Predicate::querieToString(std::vector<Predicate>& querieList)
{
	std::cout << "Queries(" << querieList.size() << "):\n";
	for (size_t i = 0; i < querieList.size(); i++)
	{
		std::cout << "  " << querieList[i].ID << "(";
		std::cout << querieList[i].para_list[0].Parameter::getContent();
		for (size_t j = 1; j < querieList[i].para_list.size(); j++)
			std::cout << "," << querieList[i].para_list[j].Parameter::getContent();
		std::cout << ")?" << std::endl;
	}

}

void Predicate::domainToString(std::set<std::string>& domain_list)
{
		std::cout << "Domain(" << domain_list.size() << "):\n";
		for (std::set<std::string>::iterator s = domain_list.begin(); s != domain_list.end(); s++)
		{
			std::cout << "  " << *s;
			//std::set<std::string>::iterator temp_iterate = s;
			//if (temp_iterate++ != domain_list.end())
				std::cout << std::endl;
		}
}