#include "Parser.h"
#include <algorithm>
// Am creating a copy of these objects in memory, but it is a way to not need to create a temp variable (same memory result)
void Parser::parse(std::vector<Token*> tokens)
{
	int follow_grammar = 0;
	//data_log.parse(tokens, grow_productions, grow_rules, data_log.scheme_list, data_log.fact_list, data_log.rule_list, data_log.querie_list);
	while (!tokens.empty() && tokens[0]->getType() != TokenType::EOF_TYPE)
	{
		data_log.parse_data(tokens, grow_productions, grow_rules, follow_grammar, data_log.scheme_list, data_log.fact_list, data_log.rule_list, data_log.querie_list);
		if(!tokens.empty() && tokens[0]->getType() != TokenType::ID)
		follow_grammar++;
	}
	if(!tokens.empty())
	data_log.toString();

}
