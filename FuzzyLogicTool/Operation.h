#pragma once
#include "Rule.h"
class Operation
{
public:
	Operation();
	~Operation();
	void AddRule(const bool& is_consequence);
	void AddSetData(const std::string &data, const int &index,const bool& has_operator, const bool& is_consequence);

	

	const FuzzySet GetData();
	const int GetSizeVector() { return rule_vector.size(); }
	Rule GetRuleTemplate() { return rule_template; }

	void ClearTemplate();
	void ClearRuleTemplate();
private:
	std::vector<Rule> rule_vector;

	FuzzySet fuzzy_set_template;
	Rule rule_template;
	int operator_value_template;
};

