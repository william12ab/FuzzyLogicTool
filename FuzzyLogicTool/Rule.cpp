#include "Rule.h"
void Rule::AddAntecedent(FuzzySet antecedent) {
	antecedent_vector.push_back(antecedent);
}
void Rule::AddConsequence(FuzzySet consequence) {
	consequence_vector.push_back(consequence);
}

const FuzzySet Rule::GetSetValues(const bool& is_consequence, const bool& has_operator){
	if (is_consequence){
		auto to_return = consequence_vector.back();	
		consequence_vector.pop_back();
		return to_return;
	}
	else {
		auto to_return = antecedent_vector.back();
		antecedent_vector.pop_back();
		return to_return;
	}
}

void Rule::ClearVectors() {
	antecedent_vector.clear();
	consequence_vector.clear();
}