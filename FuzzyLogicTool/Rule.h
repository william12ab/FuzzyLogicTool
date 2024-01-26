#pragma once
#include <vector>
#include "FuzzySet.h"
class Rule
{
public:
	void AddAntecedent(FuzzySet antecedent);
	void AddOperator(int operator_value);
	void AddConsequence(FuzzySet consequence);



	void test();
private:
	std::vector<FuzzySet> antecedent_vector;
	std::vector<FuzzySet> consequence_vector;
	std::vector<int> operator_vector;
};

