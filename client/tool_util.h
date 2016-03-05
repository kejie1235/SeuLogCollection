#pragma once
#include <string>
#include <boost\lexical_cast.hpp>

class tool_util
{
public:
	tool_util(void);
	~tool_util(void);

	void static leave_two_point(double num, std::string &dst);
};

