#include "Interpreter.h"

Relation* Interpreter::evaluatePredicate(const Predicate& p)
{
	std::string p_ID = "";
	p_ID = p.ID;
	Relation* current_relation = current_database.getRelationFromKey(p_ID);
	return current_relation;
}