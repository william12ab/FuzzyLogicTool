#include "Rule.h"
#include <algorithm>
void Rule::AddAntecedent(FuzzySet antecedent) {
	antecedent_vector.push_back(antecedent);
}
void Rule::AddConsequence(FuzzySet consequence) {
	consequence_vector.push_back(consequence);
}

const FuzzySet Rule::GetSetValues(const bool& is_consequence, const bool& has_operator, int& counter_){
	if (is_consequence){
		auto to_return = consequence_vector.back();	
		//consequence_vector.pop_back();
		return to_return;
	}
	else {
		if (counter_ > 0) {
			counter_--;
		}
		auto to_return = antecedent_vector.at(counter_);

		//auto to_return = antecedent_vector.back();
		//antecedent_vector.pop_back();
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
		auto temp = std::max_element(fuzzy_values.begin(), fuzzy_values.end());
		rule_fuzzy_value = *temp;
	}
	else if (antecedent_vector[0].GetOperatorValue() == 2) {
		auto temp=std::min_element(fuzzy_values.begin(), fuzzy_values.end());
		rule_fuzzy_value = *temp;
	}
	else {
		rule_fuzzy_value = fuzzy_values[0];
	}
	index = antecedent_vector.size();
	return index;
}