#pragma once
#include <string>
#include "Operation.h"
class DemoWindow
{
public:
	void CreateOpertation();
	void CreateRule(std::string & n, FuzzySet&antecedent, Rule&new_rule,int & operator_value,Operation &new_operation);
	void GetAntecedentValues(std::string& n, FuzzySet& antecedent, Rule& new_rule, int operator_value);
	void GetOperatorValue(std::string& n, int& operator_value, Rule& new_rule, FuzzySet& antecedent);
	void GetConsequenceValues(std::string & n, FuzzySet & consequence, Rule& new_rule);

};

