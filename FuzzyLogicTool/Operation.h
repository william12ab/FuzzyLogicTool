#pragma once
#include "Rule.h"

class Operation
{
public:
	Operation();
	~Operation();
	void AddRule(const bool& is_consequence, int&counter_,const bool& is_validate);
	void AddSetData(const std::string &data, const int &index,const bool& has_operator, const bool& is_consequence);

	
	const std::vector<Rule> GetRuleVector() const { return rule_vector; }

	const FuzzySet GetData(int& counter_);
	const int GetSizeVector() { return rule_vector.size(); }
	Rule GetRuleTemplate() { return rule_template; }

	void ClearTemplate();
	void ClearRuleTemplate();

	void PerformOperation(const std::vector<float> &defuzzy_values);

	void SortPoints();

	bool ValidateData(const bool& is_cons, const int& counter_);
	void AddUp(int& counter, const FuzzySet& temp_set);

	void ReplaceData(Rule temp_info, const int& rule_index);

	void ClearOperationValues();
private:
	std::vector<Rule> rule_vector;

	FuzzySet fuzzy_set_template;
	Rule rule_template;
	int operator_value_template;
};

