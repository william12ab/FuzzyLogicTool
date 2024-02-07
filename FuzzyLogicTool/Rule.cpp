#include "Rule.h"
#include <algorithm>
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

const int Rule::OperationWork(const std::vector<float>& defuzzy_values) {
	int index = 0;
	for (size_t i = 0; i < antecedent_vector.size(); i++){
		auto val = calculator.CalculateFuzzyValue(antecedent_vector[i],defuzzy_values[i]);
		fuzzy_values.push_back(val);
	}
	if (antecedent_vector[0].GetOperatorValue()==1){
		auto rule_fuzz_value = std::max_element(fuzzy_values.begin(), fuzzy_values.end());
	}
	else if (antecedent_vector[0].GetOperatorValue() == 2) {
		auto rule_fuzzy_value=std::min_element(fuzzy_values.begin(), fuzzy_values.end());
	}
	else {
		rule_fuzzy_value = fuzzy_values[0];
	}
	index = antecedent_vector.size();
	return index;
}