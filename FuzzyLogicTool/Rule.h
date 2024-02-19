#pragma once
#include <vector>
#include "FuzzySet.h"
#include "MathsOperator.h"
class Rule
{
public:
	void AddAntecedent(FuzzySet antecedent);
	void AddConsequence(FuzzySet consequence);
	void ClearVectors();

	const FuzzySet GetSetValues(const bool& is_consequence, const bool& has_operator,int&counter_);
	const int GetSizeOfAntecedent() { return antecedent_vector.size(); }
	
	const std::vector<FuzzySet> GetAntecedentVector() const{ return antecedent_vector; }
	const std::vector<FuzzySet> GetConsequenceVector() const { return consequence_vector; }

	const int OperationWork(const std::vector<float> &defuzzy_values);

	void ChangeInAntecedent() { antecedent_vector.pop_back(); }


	const float GetOperatorValue() const { return rule_fuzzy_value; }
private:
	std::vector<FuzzySet> antecedent_vector;
	std::vector<FuzzySet> consequence_vector;

	std::vector<float> fuzzy_values;
	float rule_fuzzy_value;
	MathsOperator calculator;
};

