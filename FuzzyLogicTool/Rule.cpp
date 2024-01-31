#include "Rule.h"
void Rule::AddAntecedent(FuzzySet antecedent) {
	antecedent_vector.push_back(antecedent);
}
void Rule::AddOperator(int operator_value) {
	operator_vector.push_back(operator_value);
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
	/*	if (has_operator) {
			operator_vector.pop_back();
		}*/
		auto to_return = antecedent_vector.back();
		antecedent_vector.pop_back();
		return to_return;
	}
}