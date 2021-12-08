#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#ifndef HEADER_H
#define HEADER_H

class Header
{
private:
	std::vector<std::string> attributes;
public:
	Header(std::vector<std::string> attributes)
	{
		this->attributes = attributes;
	}
	Header()
	{}

	std::vector<std::string> getAttributes()
	{
		return attributes;
	}

	int getAttributesSize()
	{
		return attributes.size();
	}

	std::string get_specific_attribute(int i)
	{
		return attributes[i];
	}

	Header combineHeaders(std::vector<std::string> first_relation, std::vector<std::string> second_relation, std::vector<std::pair<long unsigned int,long unsigned int>> &matching_headers)
	{
		std::vector<std::string> combined_header = first_relation;
		for (long unsigned int i = 0; i < second_relation.size(); i++)
		{
			if (std::find(combined_header.begin(), combined_header.end(), second_relation[i]) == combined_header.end())
			{
				combined_header.push_back(second_relation[i]);
			}
			else
			{
				std::vector<std::string>::iterator it = std::find(combined_header.begin(), combined_header.end(), second_relation[i]);
				int index = it - combined_header.begin();
				//std::make_pair(index, i)
				//SECOND TUPLE IS FIRST IN MATCHING
				matching_headers.push_back(std::make_pair(i, index));
			}
		}
		Header new_header = Header(combined_header);
		return new_header;
	}
};

#endif