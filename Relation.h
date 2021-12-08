#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <iterator>
#include <ostream>
#include "Parameter.h"
#include "Tuple.h"
#include "Header.h"
#ifndef RELATION_H
#define RELATION_H


class Relation
{
private:
	std::string name = "";
	Header* header = {};
	std::set<Tuple> rows = {};
public:

	Relation(std::string name = "", std::vector<std::string> dummy_parameter_list = {})
	{
		this->name = name;
		this->header = new Header(dummy_parameter_list);

	}
	Relation(std::string name, std::vector<std::string> dummy_parameter_list, std::set<Tuple> rows)
	{
		this->name = name;
		this->header = new Header(dummy_parameter_list);
		this->rows = rows;
	}
	std::string getName()
	{
		return name;
	}

	std::set<Tuple>& getRows()
	{
		return rows;
	}

	Header* getHeader()
	{
		return header;
	}

	int getRowSize()
	{
		return rows.size();
	}
	//TODO: Change findTuple to only find the correct identifier (right now, find (b,b) is finding (b,c) and (b,b)).


	void addTuple(Tuple current_tuple)
	{
		rows.insert(current_tuple);
	}
	//Not optimized. could return an index to search instead of looping through the whole set of tuples. 
	Relation* select(int position, std::string value)
	{
		std::set<Tuple>::iterator it;

		Relation* temp_relation = new Relation(this->getName(), this->header->getAttributes());

		for (it = this->rows.begin(); it != rows.end(); it++)
		{
			Tuple loopTuple = *it;
				if (loopTuple.getValue(position) == value)
				{
					temp_relation->addTuple(loopTuple);
				}
		}
		return temp_relation;
	}
	Relation* select(int original_index, int second_index)
	{
		std::set<Tuple>::iterator it;
		Relation* temp_relation = new Relation(this->getName(), this->header->getAttributes());
		for (it = this->rows.begin(); it != rows.end(); it++)
		{
			Tuple loopTuple = *it;
			if (loopTuple.getValue(original_index) == loopTuple.getValue(second_index))
			{
				temp_relation->addTuple(loopTuple);
			}
		}

		return temp_relation;
	}

	Relation* project(std::vector<std::string> alpha_map, std::map<std::string, int> mymap)
	{
		std::set<Tuple>::iterator it;
		std::map<std::string, int>::iterator mapit;
		std::vector<int> index_to_keep;
		Relation* temp_relation = new Relation(this->getName(), this->header->getAttributes());
		Tuple* new_tuple;

		for (std::string s : alpha_map)
		{
			index_to_keep.push_back(mymap[s]);
		}


		for (it = this->rows.begin(); it != rows.end(); it++)
		{
			Tuple loopTuple = *it;
			std::vector<std::string> current_values;
			for (int i = 0; i < loopTuple.size(); i++)
			{
				if (std::find(index_to_keep.begin(), index_to_keep.end(), i) != index_to_keep.end())
					current_values.push_back(loopTuple.getValue(i));
			}
			new_tuple = new Tuple(current_values);
			temp_relation->addTuple(*new_tuple);
		}

		return temp_relation;
		//Based off of combined_header size
		//No need to check for duplicates
	}
	Relation* rename(std::vector<std::string> alpha_map)
	{
		Relation* temp_relation = new Relation(this->getName(), alpha_map, this->rows);
		return temp_relation;
	}

	Relation* join(Relation* joinee)
	{
		std::vector<std::pair<long unsigned int, long unsigned int>> matching_headers;
		Header combined_header = this->header->combineHeaders(this->header->getAttributes(), joinee->header->getAttributes(), matching_headers);

		Relation* new_relation = new Relation(this->getName(), combined_header.getAttributes());

		//Second tuple is first in matching
		std::set<Tuple> first_tuple_values = this->getRows();

		//Problem: It is only grabbing the first tuple of the first relation, and not grabbing the rest
		for (Tuple i : this->rows)
		{

			//EXPERIMENT: USING DOUBLE FOR-LOOP
			for (Tuple j : joinee->rows)
			{
				//EXPERIMENT
				bool can_join = false;
				can_join = i.isJoinable(i, j, matching_headers);
				if (can_join)
				{
					//Combine tuples is busted
					Tuple new_tuple = i.combineTuples(i, j, matching_headers, combined_header.getAttributesSize());
					new_relation->addTuple(new_tuple);
				}
			}
		}
		return new_relation;
	}


	void toString()
	{
		if (this->getRowSize() == 0)
			std::cout << " No\n";
		else
		{
			std::cout << " Yes(" + std::to_string(this->getRowSize()) << ")\n";
			std::set<Tuple>::iterator it;
			for (it = this->rows.begin(); it != this->rows.end(); it++)
			{
				Tuple loopTuple = *it;
				//output += "  ";
				for (int i = 0; i < loopTuple.size(); i++)
				{
					if (i == 0)
					{
						std::cout << "  ";
					}
					std::cout << this->header->get_specific_attribute(i)<< "=";
					std::cout <<  loopTuple.getValue(i) + "";
					if (i + 1 != loopTuple.size())
						std::cout << ", ";
				}
				//std::set<Tuple>::iterator new_line = it;
				//new_line++;
				if(loopTuple.size() != 0) //&& new_line != this->rows.end())
					std::cout << std::endl;
			}
			//std::cout << output;
		}
	}

	Relation* evaluatePredicate(Predicate p, std::vector <std::pair<int, std::string>> &header_position)
	{
		//std::vector<std::string> dummy_parameter_list, std::set<Tuple> rows
		Relation new_relation = *this;
		Relation* newer_relation = &new_relation;
		std::vector<std::string> dummy_parameter_list;
		int parameter_index = 0;
		for (Parameter a : p.para_list)
		{
			if (a.getContent().at(0) == '\'')
			{
				//Need a way to get rid of M for tuple
				newer_relation = newer_relation->select(parameter_index, a.getContent());
				std::set<Tuple> new_tuple_set;
				for (Tuple t : newer_relation->getRows())
				{
					for (std::string s : t.getValues())
					{
						if (s == a.getContent())
						{
							t.removeValue(s);
						}
					}
					new_tuple_set.insert(t);
				}
				newer_relation->newRows(new_tuple_set);
				//Delete monday index from select
			}
			else
			{
				dummy_parameter_list.push_back(a.getContent());
				header_position.push_back(std::make_pair(parameter_index, a.getContent()));
				//EXPERIMENT: ADD HEADER POSITIONS TO THE HEADER POSITION VECTOR
			}
			parameter_index++;
		}
		Relation* real_new_relation = new Relation(newer_relation->getName(), dummy_parameter_list, newer_relation->rows);
		return real_new_relation;
	}

	void newRows(std::set<Tuple> new_tuple_set)
	{
		rows = new_tuple_set;
	}

	Relation* ruleProject(Predicate headPredicate)
	{
		std::vector<int> matching_attributes;
		std::vector<std::string> head_attributes;		
		for (Parameter p : headPredicate.para_list)
		{
			//head_attributes.push_back(p.getContent());
			for (int i = 0; i < this->header->getAttributesSize(); i++)
			{
				if (this->header->get_specific_attribute(i) == p.getContent())
				{
					matching_attributes.push_back(i);
					break;
				}
			}
		}
		std::set<Tuple> new_tuple_set;
		Tuple new_tuple;
		for (int i : matching_attributes)
		{
			head_attributes.push_back(this->header->get_specific_attribute(i));
		}
		for (Tuple t : this->getRows())
		{
			for (int i : matching_attributes)
			{
				new_tuple.addValue(t.getValue(i));
			}
			new_tuple_set.insert(new_tuple);
			new_tuple.clear();
		}

		Relation* new_relation = new Relation(this->name, head_attributes, new_tuple_set);
		return new_relation;
	}

	bool unionize(Relation* database_relation)
	{
		bool new_tuple_added = false;
		for (Tuple t : this->rows)
		{
			if (database_relation->getRows().insert(t).second)
			{
				new_tuple_added = true;
				std::cout << "  ";
				for (long unsigned int i = 0; i < t.getValues().size(); i++)
				{
					std::cout << database_relation->getHeader()->get_specific_attribute(i);
					std::cout << "=" << t.getValue(i);
					if (i < t.getValues().size() - 1)
					{
						std::cout << "," << " ";
					}
					else
					{
						std::cout << std::endl;
					}
				}
			}

		}
		return new_tuple_added;
	}

	bool areEqual(Relation* comparee)
	{
		if (this->getName() == comparee->getName() && this->getHeader()->getAttributes() == comparee->getHeader()->getAttributes())
		{
			std::set<Tuple> current_set = this->getRows();
			std::set<Tuple> database_set = comparee->getRows();

			if (current_set.size() != database_set.size())
			{
					return false;
			}

			std::set<Tuple>::iterator database_set_it = database_set.begin();

			for ( Tuple t : current_set)
			{
				Tuple g = *database_set_it;

				if (t.differentValues(g))
				{
					return false;
				}
				database_set_it++;
			}


		}
		else
		{
			return false;
		}
		return true;
	}
};
#endif