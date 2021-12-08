#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
#ifndef TUPLE_H
#define TUPLE_H


class Tuple
{
private:
	std::vector<std::string> values;
	bool displayed;
	int previous_size;
public:

	Tuple(std::vector<std::string> values = {}, bool displayed = false)
	{
		this->values = values;
	}

	bool operator< (const Tuple &rhs) const 
	{
		return values < rhs.values;
	}


	bool getDisplayed()
	{
		return displayed;
	}

	void setDisplayed(bool input)
	{
		displayed = input;
	}

	int getPrevious()
	{
		return previous_size;
	}

	void setPrevious(int input)
	{
		previous_size = input;
	}

	std::string getValue(size_t j)
	{
		return values[j];
	}

	std::vector<std::string> getValues()
	{
		return values;
	}

	void clear()
	{
		values.clear();
	}

	void addValue(std::string current_value)
	{
		values.push_back(current_value);
	}

	int size()
	{
		return values.size();
	}

	void removeValue(std::string value)
	{
		std::vector<std::string>::iterator found_value = std::find(values.begin(), values.end(), value);
		int index = found_value - values.begin();
		values.erase(values.begin() + index);
	}

	bool isJoinable(Tuple first_tuple, Tuple second_tuple, std::vector<std::pair<long unsigned int, long unsigned int>> matching_headers)
	{
		//pair of vector passed into isJoinable
		//More than one place they could match
		//vector of int pairs for matching
		//pair data structure
		//loop inside isJoinable


		std::vector<int> second_matching;
		for (std::pair<int, int> p : matching_headers)
		{
			second_matching.push_back(p.first);
		}
		//EXPERIMENT

		for (std::vector<std::pair<long unsigned int, long unsigned int>>::iterator it = matching_headers.begin(); it != matching_headers.end(); it++)
		{
			std::pair<int, int> current_pair = *it;
			if (second_tuple.getValue(current_pair.first) != first_tuple.getValue(current_pair.second))
			{
				return false;
			}
		}
		return true;
	}
	Tuple combineTuples(Tuple first_tuple, Tuple second_tuple, std::vector<std::pair<long unsigned int, long unsigned int>> matching_headers, long unsigned int combined_header_size)
	{

		std::vector<std::string>tuple_addition = first_tuple.getValues();

		if (matching_headers.empty())
		{
			for (int i = 0; i < second_tuple.size(); i++)
			{
				tuple_addition.push_back(second_tuple.getValue(i));
			}
		}
		else
		{
			long unsigned int iterate_second = 0;
			long unsigned int iterate_headers = 0;
			while (tuple_addition.size() != combined_header_size)
			{
				if (iterate_second != matching_headers[iterate_headers].first)
				{
					tuple_addition.push_back(second_tuple.getValue(iterate_second));
				}
				else
				{
					if(matching_headers.size() != iterate_headers+1)
					iterate_headers++;
				}
				iterate_second++;
			}
		}
		Tuple new_tuple = Tuple(tuple_addition);
		return new_tuple;
	}

	bool differentValues(Tuple second_tuple)
	{
		if (values != second_tuple.getValues())
			return true;
		return false;
	}

};

#endif