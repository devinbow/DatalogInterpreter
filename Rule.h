// This is Rule for project 2
#ifndef RULE_H
#define RULE_H
#include "Token.h"
#include "Predicate.h"
#include <vector>
class Rule
{
	Predicate headPredicateObj;
	std::vector<Predicate>bodyPredicates;
	int graph_number = 0;
public:
	void parseRules(std::vector<Token*>& tokens, std::vector<Rule>& ruleList);
	void headPredicate(std::vector<Token*>& tokens, int current_index, std::vector<Rule>& ruleList);
	void IDList(std::vector<Token*> const tokens, int& current_index);
	void predicate(std::vector<Token*> const tokens, int& current_index);
	void parameter(std::vector<Token*> const tokens, int& current_index, std::vector<Parameter> &tempBodyParameter);
	void parameterList(std::vector<Token*> const tokens, int& current_index, std::vector<Parameter>& tempBodyParameter);
	void to_string(Rule current_rule);

	std::vector<Predicate> getBodyPrecdicates()
	{
		return this->bodyPredicates;
	}

	Rule(Predicate headPredicateObj, std::vector<Predicate> bodyPredicates)
	{
		this->headPredicateObj = headPredicateObj;
		this->bodyPredicates = bodyPredicates;
		//predicate_list.push_back(tokens);
	}
	Rule()
	{}

	void setGraphNumber(int graph_number)
	{
		this->graph_number = graph_number;
	}

	int getGraphNumber()
	{
		return graph_number;
	}
	static void ruleToString(std::vector<Rule> const& ruleList);

	Predicate getHeadPredicate()
	{
		return headPredicateObj;
	}

	std::vector <std::pair<int, std::string>> get_head_header_positions()
	{
		std::vector <std::pair<int, std::string>> head_header_positions;
		int current_index = 0;
		for (Parameter p : headPredicateObj.para_list)
		{
			head_header_positions.push_back(std::make_pair(current_index, p.getContent()));
			current_index++;
		}
		return head_header_positions;
	}
};


#endif