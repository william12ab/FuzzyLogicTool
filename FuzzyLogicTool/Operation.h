#pragma once
#include "Rule.h"
class Operation
{
public:
	Operation();
	~Operation();
	void CreateNewOperation(Rule new_rule);
private:
	std::vector<Rule> rule_vector;
};

