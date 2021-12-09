#include "DatalogProgram.h"
#include "Database.h"
#include "Schemes.h"
#include "Graph.h"

#ifndef INTERPRETER_H
#define INTERPRETER_H

/*
	HOW TO DO HEADER:

	1. Combine R1 with R2 header
		1a. Do this in join operation for R1 and R2 
	2. Project head predicate headers to developed relation 





*/


//TODO:FIGURE OUT WHY OUTPUT FOR CURRENT INPUT IS WRONG



class Interpreter
{
private:
	DatalogProgram current_program;
	Database current_database;
	//Header is parameter list
public:
	Interpreter(DatalogProgram current_program, Database current_database)
	{
		this->current_program = current_program;
		this->current_database = current_database;
	}

	Relation* evaluatePredicate(const Predicate& p);

	void inter_work()
	{
		//For each scheme
		for (Predicate p : current_program.scheme_list)
		{
			std::string p_ID = "";
			std::vector<Parameter> p_parameter_List;
			p_ID = p.ID;
			p_parameter_List = p.para_list;


			std::vector<std::string> dummy_parameter_list;
			for (Parameter pa : p_parameter_List)
			{
				dummy_parameter_list.push_back(pa.getContent());
			}

			Relation* newRelation = new Relation(p_ID, dummy_parameter_list);
			current_database.addRelation(newRelation);


		}
		for (Predicate p : current_program.fact_list)
		{
			std::vector<std::string> dummy_tuple;


			std::string p_ID = "";
			std::vector<Parameter> p_parameter_List;
			p_ID = p.ID;
			p_parameter_List = p.para_list;
			Relation* current_relation = evaluatePredicate(p);
			for (Parameter pa : p_parameter_List)
			{
				dummy_tuple.push_back(pa.getContent());
			}

			Tuple a_tuple = Tuple(dummy_tuple);
			current_relation->addTuple(a_tuple);

		}

		Graph current_graph = Graph();

	//	current_graph.assign_rule_numbers(this->current_program.rule_list);
		current_graph.createGraph(this->current_program.rule_list);

		std::vector<std::vector<int>> SCC = current_graph.getSCC();

		
		std::vector<Relation*> added_relations;
		std::vector<Relation*> initial_relations = this->current_database.getRelationsInDatabase();
		std::vector<Relation*> final_relations;

		std::vector <std::pair<int, std::string>> head_header_position;
		std::vector <std::pair<int, std::string>> body_header_position;

		//std::vector< std::vector <std::pair<int, std::string>>> vector_of_header_positions;
		int populate_schemes = 0;

		bool fixed_point = true;
		Rule current_rule;

		std::set<Tuple> already_added_tuple;
		std::set<std::string> already_added_head;

		bool run_single_check = false;
		std::cout << std::endl << "Rule Evaluation" << std::endl;
		for (std::vector<int> j : SCC)
		{
			long unsigned int counter = 0;
			std::cout << "SCC: ";
			for (int i : j)
			{
				std::cout << "R" << i;
				if (counter + 1 < j.size())
				{
					std::cout << ",";
				}
				counter++;
			}
			std::cout << std::endl;
			//While size of scc > 1 || adjacency list for rule contains itself
			//
			if (j.size() == 1)
			{
				run_single_check = true;
			}
			else
			{
				run_single_check = false;
			}
			while (fixed_point)
			{
				fixed_point = false;
				//EXPERIMENT:COMMENTING OUT THIS
				//for (long unsigned int i = 0; i < current_program.rule_list.size(); i++)
				for (int i : j)
				{
					current_rule = current_program.rule_list[i];
					head_header_position = current_rule.get_head_header_positions();

					for (Predicate p : current_program.rule_list[i].getBodyPrecdicates())
					{
						//PROBLEM: Body predicate order is not being respected
						//Problem is, added_relation is not discriminating based on the predicate. It is grabbing the whole relation.
						Relation* added_relation = new Relation();
						//second evaluatePredicate function that will select, rename, project
						//these are two different evaluatePredicate functions
						added_relation = this->evaluatePredicate(p);
						added_relation = added_relation->evaluatePredicate(p, body_header_position);
						added_relations.push_back(added_relation);
					}
					int relation_size = added_relations.size();
					if (relation_size > 1)
					{
						Relation* added_relation = new Relation();
						added_relation = added_relations[0]->join(added_relations[1]);
						added_relations.erase(added_relations.begin(), added_relations.begin() + 2);
						added_relations.insert(added_relations.begin(), added_relation);
						while (added_relations.size() > 1)
						{
							//This is a problem, added_relations cannot clear after each join since other relations will be there from earlier 
							added_relation = added_relations[0]->join(added_relations[1]);
							added_relations.erase(added_relations.begin(), added_relations.begin() + 2);
							added_relations.insert(added_relations.begin(), added_relation);
							//for some reason, not working
						}
					}
					Relation* combined_relation = added_relations[0];
					added_relations.clear();
					combined_relation = combined_relation->ruleProject(current_rule.getHeadPredicate());
					combined_relation = combined_relation->rename(this->current_database.getRelationFromKey(current_rule.getHeadPredicate().ID)->getHeader()->getAttributes());


					//This section of code is awful, and only exists because I am too lazy to debug the actual issue.

					Relation* new_relation = new Relation(combined_relation->getName(), combined_relation->getHeader()->getAttributes());
					int g = new_relation->getHeader()->getAttributesSize();
					for (Tuple t : combined_relation->getRows())
					{
						if (t.size() == g)
							new_relation->addTuple(t);
					}
					combined_relation = new_relation;

					//End of horrible code



					//isEqual before unionization

					current_rule.to_string(current_rule);
					fixed_point = combined_relation->unionize(this->current_database.getRelationFromKey(current_rule.getHeadPredicate().ID)) | fixed_point;

				}
				populate_schemes++;

				if (run_single_check)
				{
					if(!current_graph.check_for_adjacency(current_rule))
					break;
				}
			}
			//This is added so that the next start for the forest doesn't immediately chop off the tree.
			if (!fixed_point)
			{
				fixed_point = true;
			}

			std::cout << populate_schemes << " passes: ";
			counter = 0;
			for (int i : j)
			{
				std::cout << "R" << i;
				if (counter + 1 < j.size())
				{
					std::cout << ",";
				}
				counter++;
			}
			std::cout << std::endl;
			populate_schemes = 0;
		}

		std::cout << std::endl << "Query Evaluation" << std::endl;
		for(size_t i = 0 ; i < current_program.querie_list.size() ; i++)
		{
			Relation* current_relation = evaluatePredicate(current_program.querie_list[i]);
			//std::cout << current_program.querie_list[i];
			std::cout << "" << current_program.querie_list[i].ID << "(";
			std::cout << current_program.querie_list[i].para_list[0].Parameter::getContent();
			for (size_t j = 1; j < current_program.querie_list[i].para_list.size(); j++)
				std::cout << "," << current_program.querie_list[i].para_list[j].Parameter::getContent();
			std::cout << ")?";
			
			//EXPERIMENT:CURRENTLY CHANGING PRE-SET RELATIONS DURING LOOP. COPY ELEMENTS TO ANOTHER POINTER IF THIS CAUSES ISSUES LATER. 
				std::map<std::string, int> repeat_variable = {};
				std::vector<std::string> alpha_map = {};
				for (size_t h = 0; h < current_program.querie_list[i].para_list.size(); h++)
				{
					//j is just what the parameter is
					//Constant is a string
					if (current_program.querie_list[i].para_list[h].getType() == "STRING")
					{
						//current_relation->findTuple(p_parameter_List[h].getContent(), h);
						current_relation = current_relation->select(h, current_program.querie_list[i].para_list[h].getContent());
						
					}
					if (current_program.querie_list[i].para_list[h].getType() == "ID")
					{
						std::string current_ID = current_program.querie_list[i].para_list[h].getContent();
						//current_relation = current_relation->select(current_relation, current_ID);
						
						if (repeat_variable.count(current_ID))
						{
							int original_location = repeat_variable[current_ID];
							int second_location = h;
							current_relation = current_relation->select(original_location, second_location);

						}
						else
						{
							repeat_variable[current_ID] = h;
							alpha_map.push_back(current_ID);
						}
					}

				}
			//This is where I start project
			current_relation = current_relation->project(alpha_map, repeat_variable);
			current_relation = current_relation->rename(alpha_map);
			current_relation->toString();
		}
	}
	//Check if itself is in its adjacency list
	//If they match, loop
	//If not, don't loop
};

#endif 