#pragma once
#include "Rule.h"

class Operation
{
public:
	Operation();
	~Operation();
	void AddRule(const bool& is_consequence);
	void AddSetData(const std::string &data, const int &index,const bool& has_operator, const bool& is_consequence);

	
	const std::vector<Rule> GetRuleVector() const { return rule_vector; }

	const FuzzySet GetData();
	const int GetSizeVector() { return rule_vector.size(); }
	Rule GetRuleTemplate() { return rule_template; }

	void ClearTemplate();
	void ClearRuleTemplate();

	void PerformOperation(const std::vector<float> &defuzzy_values);

	void SortPoints();

	bool ValidateData(const bool& is_cons);
	void AddUp(int& counter, const FuzzySet& temp_set);
private:
	std::vector<Rule> rule_vector;

	FuzzySet fuzzy_set_template;
	Rule rule_template;
	int operator_value_template;
};

