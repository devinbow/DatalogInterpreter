#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "DatalogProgram.h"
#include "Rule.h"
#include "Predicate.h"
class Parser
{
	Predicate grow_productions;
	Rule grow_rules;
	DatalogProgram data_log;
public:
	void parse(std::vector<Token*> tokens);
	DatalogProgram getProgram()
	{
		return data_log;
	}
	//DatalogProgram parse_list();
};


#endif 