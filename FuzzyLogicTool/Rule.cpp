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
		return to_return;
	}
	else {
		if (counter_ > 0) {
			counter_--;
		}
		if (antecedent_vector.size()>counter_){
			auto to_return = antecedent_vector.at(counter_);
			return to_return;
		}
		else {
			FuzzySet s;
			return s;
		}
	}
}

void Rule::ClearVectors() {
	antecedent_vector.clear();
	consequence_vector.clear();
}

void Rule::ClearValues() {
	fuzzy_values.clear();
	human_values.clear();
	rule_fuzzy_value = 0.f;
}
const int Rule::OperationWork(const std::vector<float>& defuzzy_values) {
	int index = 0;
	for (size_t i = 0; i < antecedent_vector.size(); i++){
		auto val = calculator.CalculateFuzzyValue(antecedent_vector[i],defuzzy_values[i]);
		fuzzy_values.emplace_back(val);
		human_values.emplace_back(defuzzy_values[i]);
	}
	if (antecedent_vector[0].GetOperatorValue()!=0){
		float first_vlaue = fuzzy_values[0];
		for (size_t i = 0; i < antecedent_vector.size()-1; i++){
			if (antecedent_vector[i].GetOperatorValue()==1) {
				auto max = std::max(first_vlaue, fuzzy_values[i + 1]);
				first_vlaue = max;
			}
			if (antecedent_vector[i].GetOperatorValue() == 2){
				auto min = std::min(first_vlaue, fuzzy_values[i + 1]);
				first_vlaue = min;
			}
		}
		rule_fuzzy_value = first_vlaue;
	}
	else {
		rule_fuzzy_value = fuzzy_values[0];
	}
	index = antecedent_vector.size();
	return index;
}