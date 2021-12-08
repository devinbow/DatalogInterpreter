#ifndef PREDICATE_H
#define PREDICATE_H
#include "Token.h"
#include "Parameter.h"
#include <vector>
#include <set>
class Predicate
{
public:
	Predicate(std::string ID, std::vector<Parameter> para_list)
	{
		this->ID = ID;
		this->para_list = para_list;
			//predicate_list.push_back(tokens);
	}
	std::string ID;
	std::vector<Parameter>para_list;
	Predicate() {}
	void IDList(std::vector<Token*>&tokens, int &current_index);
	void stringList(std::vector<Token*>&tokens, int& current_index);
	void parseScheme(std::vector<Token*> &tokens, std::vector<Predicate> &schemeList);
	void predicateParse(std::vector<Token*>& tokens, int& current_index, std::vector<Predicate>& querieList);
	void parameter(std::vector<Token*>&tokens, int& current_index, std::vector<Parameter>& tempBodyParameter);
	void parameterList(std::vector<Token*>&tokens, int& current_index, std::vector<Parameter>& tempBodyParameter);
	void parseFacts(std::vector<Token*>& tokens, std::vector<Predicate>& factsList);
	void parseQueries(std::vector<Token*>& tokens, std::vector<Predicate>& querieList);

	static void schemeToString(std::vector<Predicate> & schemeList);
	static void factToString(std::vector<Predicate> & factsList, std::set<std::string>& domain_list);
	static void querieToString(std::vector<Predicate> & querieList);
	static void domainToString(std::set<std::string>& domain_list);

};


#endif