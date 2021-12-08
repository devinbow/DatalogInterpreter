#include "Rule.h"

#ifndef NODE_H
#define NODE_H
class Node {
private:
	int id = 0;
	bool visited = false;
	Rule current_rule;
public:
	Node(int value)
	{
		id = value;
	}

	void setVisited(bool visited)
	{
		this->visited = visited;
	}
	bool getVisited()
	{
		return visited;
	}

	void setRule(Rule current_rule)
	{
		this->current_rule = current_rule;
	}

	Rule getRule()
	{
		return current_rule;
	}

	int getID()
	{
		return id;
	}
};
#endif