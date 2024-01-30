#pragma once
#include "Rule.h"
class Operation
{
public:
	Operation();
	~Operation();
	void AddRule(const bool& is_antecedent);

	void AddSetData(const std::string &data, const int &index,const bool& has_operator);

	void ClearTemplate();
private:
	std::vector<Rule> rule_vector;

	FuzzySet fuzzy_set_template;
	Rule rule_template;
	int operator_value_template;
};

