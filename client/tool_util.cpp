#include "tool_util.h"


tool_util::tool_util(void)
{
}


tool_util::~tool_util(void)
{
}

void tool_util::leave_two_point(double num, std::string &dst){

	std::string tmp = boost::lexical_cast<std::string>(num);
	size_t location = tmp.find('.');

	dst = tmp.substr(0, location+3);
}
