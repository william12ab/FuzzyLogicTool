#pragma once
#include <vector>
#include "FuzzySet.h"
class Rule
{
public:
	void AddAntecedent(FuzzySet antecedent);
	void AddConsequence(FuzzySet consequence);
	void ClearVectors();

	const FuzzySet GetSetValues(const bool& is_consequence, const bool& has_operator);
	const int GetSizeOfAntecedent() { return antecedent_vector.size(); }
	
	const std::vector<FuzzySet> GetAntecedentVector() const{ return antecedent_vector; }
	const std::vector<FuzzySet> GetConsequenceVector() const { return consequence_vector; }

private:
	std::vector<FuzzySet> antecedent_vector;
	std::vector<FuzzySet> consequence_vector;
};

