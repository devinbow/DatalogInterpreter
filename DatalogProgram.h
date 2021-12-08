#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include "Parameter.h"
#include "Rule.h"
#include "Token.h"
#include "Predicate.h"
#include <string>
#include <vector>
#include <iostream>
#include <set>
class DatalogProgram
{
public:
	DatalogProgram()
	{
	}
	std::vector<Predicate> scheme_list;
	std::vector<Predicate> fact_list;
	std::vector<Predicate> querie_list;
	std::vector<Rule> rule_list;
	std::set<std::string>domain_list;
	//CHANGED: REMOVED toSTRING 
	void toString()
	{
		//Predicate::schemeToString(scheme_list);
		//Predicate::factToString(fact_list, domain_list);
		//Rule::ruleToString(rule_list);
		//Predicate::querieToString(querie_list);
		//Predicate::domainToString(domain_list);
	}

	void parse_data(std::vector<Token*>& tokens, Predicate grow_productions, Rule grow_rules, int& follow_grammar, std::vector<Predicate>& scheme_list, std::vector<Predicate>& fact_list, std::vector<Rule>& rule_list, std::vector<Predicate>& querie_list)
	{
		try
		{

			while (tokens[0]->getType() == TokenType::COMMENT)
			{
				tokens.erase(tokens.begin());
			}

			if (tokens[0]->getType() == TokenType::SCHEMES && tokens[1]->getType() == TokenType::COLON)
			{
				//if (!fact_list.empty() || !rule_list.empty() || !querie_list.empty())
				//	throw(tokens[0]);
				if(follow_grammar != 0)
					throw(tokens[0]);
				tokens.erase(tokens.begin());
				tokens.erase(tokens.begin());
				if (tokens[0]->getType() != TokenType::FACTS)
				{
					if (tokens[0]->getType() != TokenType::EOF_TYPE)
						grow_productions.parseScheme(tokens, scheme_list);
				}
			}
			else if (tokens[0]->getType() == TokenType::FACTS && tokens[1]->getType() == TokenType::COLON)
			{
				//if (!rule_list.empty() || !querie_list.empty())
				//	throw(tokens[0]);
				if (follow_grammar != 1 || scheme_list.empty())
					throw(tokens[0]);
				tokens.erase(tokens.begin());
				tokens.erase(tokens.begin());
				if (tokens[0]->getType() != TokenType::RULES)
				{
					if(tokens[0]->getType() != TokenType::EOF_TYPE)
						grow_productions.parseFacts(tokens, fact_list);
				}
			}
			else if (tokens[0]->getType() == TokenType::RULES && tokens[1]->getType() == TokenType::COLON)
			{
			//	if (!querie_list.empty())
			//		throw(tokens[0]);
				if (follow_grammar != 2)
					throw(tokens[0]);
				tokens.erase(tokens.begin());
				tokens.erase(tokens.begin());
				if (tokens[0]->getType() != TokenType::QUERIES)
				{
					if (tokens[0]->getType() != TokenType::EOF_TYPE)
						grow_rules.parseRules(tokens, rule_list);
				}
			}
			else if (tokens[0]->getType() == TokenType::QUERIES && tokens[1]->getType() == TokenType::COLON)
			{
				if (follow_grammar != 3)
					throw(tokens[0]);
				tokens.erase(tokens.begin());
				tokens.erase(tokens.begin());
				if (tokens[0]->getType() != TokenType::EOF_TYPE)
					grow_productions.parseQueries(tokens, querie_list);
			}
			else
			{
				if(tokens[1]->getType() != TokenType::COLON)
					throw(tokens[1]);
				throw(tokens[0]);

			}
		}
		catch (Token* error_token)
		{
			std::cout << "Failure!\n  (" << error_token->tokenToString(error_token->getType()) << ",\"" << error_token->getDescription() << "\"," << error_token->getLine_s() << ")";
			tokens.clear();
			return;
		}
	}

};

#endif