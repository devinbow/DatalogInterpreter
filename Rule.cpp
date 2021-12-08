#include "Rule.h"
#include "Parameter.h"
#include <iostream>
void Rule::parseRules(std::vector<Token*>& tokens, std::vector<Rule>& ruleList)
{
	do
	{
		int calc_rule = 0;
		headPredicate(tokens, calc_rule, ruleList);
		if (tokens.empty())
			return;
		Rule temp_rule = Rule(headPredicateObj, bodyPredicates);
		ruleList.push_back(temp_rule);
		bodyPredicates.clear();
		//Need a way to recognize that there is a list
	} while (tokens[0]->getType() == TokenType::ID);

}
void Rule::headPredicate(std::vector<Token*>& tokens, int current_index, std::vector<Rule>& ruleList)
{
	if (tokens[current_index]->getType() == TokenType::ID)
	{
		current_index++;
		if (tokens[current_index]->getType() == TokenType::LEFT_PAREN)
		{
			current_index++;
			if (tokens[current_index]->getType() == TokenType::ID)
			{
				current_index++;
				if (tokens[current_index]->getType() != TokenType::COMMA)
				{
					if (tokens[current_index]->getType() != TokenType::RIGHT_PAREN)
					{
					//throw()
					exit(-1);
					}
				}
			}
			else
			{
				//throw()
				exit(-1);
			}
		}
		else
		{
			//throw()
			exit(-1);
		}
	}
	else
	{
		//throw()
		exit(-1);
	}

	IDList(tokens, current_index);
	if (tokens.empty())
		return;
	std::vector<Parameter> para_list;

	Parameter param = Parameter(tokens[2]->getDescription());

	//The plus one is to move from initial comma to the first ID in list
	for (int i = 2; i < current_index; i = i + 2)
	{
		param = Parameter(tokens[i]->getDescription());
		para_list.push_back(param);
	}
	//EXPERIMENT: USING STATIC NUMERAL FOR INITIALIZATION
	Predicate temp_pred = Predicate(tokens[0]->getDescription(), para_list);
	headPredicateObj = temp_pred;
	tokens.erase(tokens.begin(), tokens.begin() + current_index);
	current_index = 0;
	//std::vector<Parameter> para_list;

		if (tokens[current_index]->getType() != TokenType::COLON_DASH)
		{
			//throw()
			exit(-1);
		}
		current_index++;
		predicate(tokens, current_index);
		if (tokens.empty())
			return;
		tokens.erase(tokens.begin(), tokens.begin() + current_index);
		current_index = 0;
		while (tokens[current_index]->getType() == TokenType::COMMA)
		{
			current_index++;
			predicate(tokens, current_index);
			if (tokens.empty())
				return;
			tokens.erase(tokens.begin(), tokens.begin() + current_index);
			current_index = 0;
		}
		if (tokens[current_index]->getType() != TokenType::PERIOD)
		{
			//throw()
			exit(-1);
		}
		tokens.erase(tokens.begin());
		return;


}

void Rule::IDList(std::vector<Token*> const tokens, int& current_index)
{
	if ((tokens[current_index]->getType() != TokenType::RIGHT_PAREN))
	{
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
					//throw
					exit(-1);
				}
			}
			else
			{
				//throw()
				exit(-1);
			}
		} while (tokens[current_index]->getType() != TokenType::RIGHT_PAREN);
	}
	//Skips right_paren
	current_index++;
}

void Rule::predicate(std::vector<Token*> const tokens, int& current_index)
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
			bodyPredicates.push_back(temp_pred);
			return;
		}
		else
		{
			//throw
			exit(-1);
		}
	}
	else
	{
		//throw()
		exit(-1);
	}
}
void Rule::parameter(std::vector<Token*> const tokens, int& current_index, std::vector<Parameter> &tempBodyParameter)
{
	if (tokens[current_index]->getType() == TokenType::STRING || tokens[current_index]->getType() == TokenType::ID)
	{
		Parameter temp_pred = Parameter(tokens[current_index]->getDescription());
		tempBodyParameter.push_back(temp_pred);
		current_index++;
		parameterList(tokens, current_index, tempBodyParameter);
		if (tokens.empty())
			return;
		return;
	}
	else
	{
		//throw()
		exit(-1);
	}
}

void Rule::parameterList(std::vector<Token*> const tokens, int& current_index, std::vector<Parameter> &tempBodyParameter)
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
		//throw()
		exit(-1);
	}
}

void Rule::ruleToString(std::vector<Rule> const& ruleList)
{
	
	std::cout << "Rules(" << ruleList.size() << "):\n";
	for (size_t i = 0; i < ruleList.size(); i++)
	{
		std::cout << "  " << ruleList[i].headPredicateObj.ID << "(";
		for (size_t j = 0 ; j < ruleList[i].headPredicateObj.para_list.size(); j++)
		{
			std::cout << ruleList[i].headPredicateObj.para_list[j].content;
			size_t temp = j;
			if (temp++ != ruleList[i].headPredicateObj.para_list.size()-1)
				std::cout << ",";
		}
		std::cout << ") :- ";

		//std::cout << ruleList[i].bodyPredicates[0] << "(";
		for (size_t j = 0; j < ruleList[i].bodyPredicates.size(); j++)
		{
			std::cout << ruleList[i].bodyPredicates[j].ID << "(";
			for (size_t k = 0; k < ruleList[i].bodyPredicates[j].para_list.size(); k++)
			{
				std::cout << ruleList[i].bodyPredicates[j].para_list[k].content;
				size_t temp = k;
				if (temp++ != ruleList[i].bodyPredicates[j].para_list.size()-1)
					std::cout << ",";
			}
			size_t temp = j;
			if (temp++ == ruleList[i].bodyPredicates.size()-1)
				std::cout << ")." << std::endl;
			else
				std::cout << "),";
		}
	}
	//	std::cout << "  " << ruleList[i].ID << "(";
		//std::cout << ruleList[i].bodyPredicates[0].para_list[0].content;
	//		std::cout << "," << ruleList[i].bodyPredicates[j].Parameter::getContent();
	
}

void Rule::to_string(Rule current_rule)
{
	std::cout  << current_rule.getHeadPredicate().ID << "(";
	for (size_t j = 0; j < current_rule.getHeadPredicate().para_list.size(); j++)
	{
		std::cout << current_rule.getHeadPredicate().para_list[j].content;
		size_t temp = j;
		if (temp++ != current_rule.getHeadPredicate().para_list.size() - 1)
			std::cout << ",";
	}
	std::cout << ") :- ";

	//std::cout << ruleList[i].bodyPredicates[0] << "(";
	for (size_t j = 0; j < current_rule.getBodyPrecdicates().size(); j++)
	{
		std::cout << current_rule.getBodyPrecdicates()[j].ID << "(";
		for (size_t k = 0; k < current_rule.getBodyPrecdicates()[j].para_list.size(); k++)
		{
			std::cout << current_rule.getBodyPrecdicates()[j].para_list[k].content;
			size_t temp = k;
			if (temp++ != current_rule.getBodyPrecdicates()[j].para_list.size() - 1)
				std::cout << ",";
		}
		size_t temp = j;
		if (temp++ == current_rule.getBodyPrecdicates().size() - 1)
			std::cout << ")." << std::endl;
		else
			std::cout << "),";
	}
}