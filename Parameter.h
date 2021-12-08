#ifndef PARAMETER_H
#define PARAMETER_H
#include <string>
//Need extra string to check if string or ID
class Parameter
{
public:
	Parameter(std::string text, std::string type_check = "")
	{
		content = text;
		this->type_check = type_check;
	}
	std::string content = "";
	std::string type_check = "";
	std::string getContent() { return content; }
	std::string getType() { return type_check; }
};


#endif