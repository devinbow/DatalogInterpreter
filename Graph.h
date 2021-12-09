#include "Rule.h"
#include "Node.h"
#include <iterator>
#include <map>
#include <unordered_map>
#ifndef GRAPH_H
#define GRAPH_H
class Graph {
private:
	std::map<int, std::set<int>> current_edges;
	std::map<int, std::set<int>> reverse_edges;
	std::unordered_map<int, std::set<int>> new_current_edges;
	std::vector<int> post_order;
	//std::vector<int> reverse_post_order;
	//Make post_order vector of ints
	std::vector<Node> current_nodes;
	std::vector<std::vector<int>> forest;
	std::vector<int> tree;

public:
	void addNode(Node to_add)
	{
		current_nodes.push_back(to_add);
	}
	void createGraph(std::vector<Rule>& rule_list)
	{
		this->assign_rule_numbers(rule_list);
		this->createNodes(rule_list);
		this->create_and_print_Dependencies();
		this->reverseDependencyGraph();
		this->dfsForest(reverse_edges);
		this->manipulate_current_edges();
		this->dumbDFSForest(new_current_edges);
		//Now, my forest should be filled with SCC
		this->organizeForest();
		//EXPERIMENT: Looks like I need the SCC in order even though it wasn't placed in that order. This is why organization is needed.
		//this->toString();
	}

	void assign_rule_numbers(std::vector<Rule>& rule_list)
	{
		for (long unsigned int i = 0; i < rule_list.size(); i++)
		{
			rule_list[i].setGraphNumber(i);
		}
	}

	bool check_for_adjacency(Rule current_rule)
	{
		int current_graph_number = current_rule.getGraphNumber();
		std::set<int> current_connected_edges = current_edges[current_graph_number];
		for (int i : current_connected_edges)
		{
			if (i == current_graph_number)
			{
				return true;
			}
		}
		//if(std::find(current_edges.begin(), current_edges.end(), current_graph_number)
		return false;
	}

	std::vector<std::vector<int>> getSCC()
	{
		return forest;
	}


	void createNodes(std::vector<Rule>& rule_list)
	{
		for (long unsigned int i = 0; i < rule_list.size(); i++)
		{
			Node create_node = Node(i);
			create_node.setRule(rule_list[i]);
			current_nodes.push_back(create_node);
		}
	}

	void create_and_print_Dependencies()
	{
		for (long unsigned int i = 0; i < current_nodes.size(); i++)
		{
					std::set<int> connected_vertices;

					for (Predicate p : current_nodes[i].getRule().getBodyPrecdicates())
					{
						for (long unsigned int j = 0; j < current_nodes.size(); j++)
						{
							if (current_nodes[j].getRule().getHeadPredicate().ID == p.ID)
							{
								connected_vertices.insert(j);
							}
						}
					}
			std::pair<int, std::set<int>> new_pair = { i, connected_vertices };
			current_edges.insert(new_pair);
		}
		std::cout << "Dependency Graph" << std::endl;
		for (std::pair<int, std::set<int>> i : current_edges)
		{
			std::cout << "R" << i.first << ":";
			long unsigned int counter = 0;
			for (int j : i.second)
			{
				std::cout << "R" << j;
				if (counter+1 < i.second.size())
				{
					std::cout << ",";
				}
				counter++;
			}
			std::cout << std::endl;
		}
	}

	void reverseEdgePopulate(std::map<int, std::set<int>>& reverse_edges)
	{
		std::set<int> connected_vertices;

		for (std::map<int, std::set<int>>::iterator it = current_edges.begin() ; it != current_edges.end(); it++)
		{
			std::pair<int, std::set<int>> new_pair = { it->first, connected_vertices };
			reverse_edges.insert(new_pair);
		}
	}

	void reverseDependencyGraph()
	{

		std::map<int, std::set<int>> reverse_edges;
		reverseEdgePopulate(reverse_edges);
		std::set<int> new_values;
		for (std::pair<int, std::set<int>> p : current_edges)
		{
			for (int i : p.second)
			{
				//I need to grab the actual value from the map
				new_values = reverse_edges[i];
				new_values.insert(p.first);
				reverse_edges[i] = new_values;
			}
		}
		this->reverse_edges = reverse_edges;
	}

	void dfsForest(std::map<int, std::set<int>> found_edges)
	{
		forest.clear();
		for (std::pair<int, std::set<int>> p : found_edges)
		{
			current_nodes[p.first].setVisited(false);
		}
		for (std::pair<int, std::set<int>> p : found_edges)
		{
			if (!current_nodes[p.first].getVisited())
			{
				tree.push_back(current_nodes[p.first].getID());
				DepthFirstSearch(current_nodes[p.first], found_edges);
				forest.push_back(tree);
				tree.clear();
			}
		}
		//I set the reverse to the original just to keep the data temporarily
		//Make the post_order reverse
		std::reverse(post_order.begin(), post_order.end());
	}

	void DepthFirstSearch(Node& n, std::map<int, std::set<int>>& found_edges)
	{
		n.setVisited(true);
		//I start iterating through the found edges starting at the current index so that I don't go out of order
		for (int i : found_edges[n.getID()])
		{
			if (!current_nodes[i].getVisited())
			{
				tree.push_back(current_nodes[i].getID());
				DepthFirstSearch(current_nodes[i], found_edges);
			}
		}
		post_order.push_back(n.getID());
	}

	void dumbDFSForest(std::unordered_map<int, std::set<int>> &found_edges)
	{
		forest.clear();
		for (std::pair<int, std::set<int>> p : found_edges)
		{
			current_nodes[p.first].setVisited(false);
		}
		for (std::pair<int, std::set<int>> p : found_edges)
		{
			if (!current_nodes[p.first].getVisited())
			{
				tree.push_back(current_nodes[p.first].getID());
				dumbDepthFirstSearch(current_nodes[p.first], found_edges);
				forest.push_back(tree);
				tree.clear();
			}
		}
	}
	 void dumbDepthFirstSearch(Node& n, std::unordered_map<int, std::set<int>>& found_edges)
	 {
		 n.setVisited(true);
		 //I start iterating through the found edges starting at the current index so that I don't go out of order
		 for (int i : found_edges[n.getID()])
		 {
			 if (!current_nodes[i].getVisited())
			 {
				 tree.push_back(current_nodes[i].getID());
				 dumbDepthFirstSearch(current_nodes[i], found_edges);
			 }
		 }
	 }

	 void manipulate_current_edges()
	 {
		 std::unordered_map<int, std::set<int>> new_current_edges;
		 std::pair<int, std::set<int>> new_pair;
		 for (int i : post_order)
		 {
			 new_pair = std::make_pair(i, current_edges[i]);
			 new_current_edges.insert(new_pair);
		 }
		 //current_edges = new_current_edges;
		 this->new_current_edges = new_current_edges;
	 }

	 void organizeForest()
	 {
		 int keep_track = 0;
		 for (std::vector<int> i : forest)
		 {
			 std::sort(i.begin(), i.end());
			 forest[keep_track] = i;
			 keep_track++;
		 }
	 }

	void toString()
	{

		
		for (Node n : current_nodes)
		{
			std::cout << "R" << n.getID() << " ";
			n.getRule().to_string(n.getRule());
		}
		
		std::cout << std::endl << std::endl;

		for (std::pair<int, std::set<int>> p : current_edges)
		{
			std::cout << p.first << "  ";
			for (int i : p.second)
			{
				std::cout << i << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl << std::endl;

		for (std::pair<int, std::set<int>> p : reverse_edges)
		{
			std::cout << p.first << "  ";
			for (int i : p.second)
			{
				std::cout << i << " ";
			}
			std::cout << std::endl;
		}

		std::cout << std::endl << std::endl;

		for (std::vector<int> tree : forest)
		{
			for (int value : tree)
			{
				std::cout << value << std::endl;
			}
			std::cout << "END OF TREE" << std::endl;
		}

		std::cout << std::endl << std::endl;
		
		for(int i : post_order)
		std::cout << i << std::endl;
		
	}
};
#endif