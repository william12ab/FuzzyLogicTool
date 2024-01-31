#include "Operation.h"

Operation::Operation() {
	
}
Operation::~Operation() {
	if (rule_vector.size()>0){
		rule_vector.clear();
	}
}

void Operation::AddRule(const bool& is_consequence) {
	if (!is_consequence) {
		rule_template.AddAntecedent(fuzzy_set_template);
	}
	else {
		rule_template.AddConsequence(fuzzy_set_template);
		rule_vector.push_back(rule_template);
		ClearRuleTemplate();
	}
	ClearTemplate();
}
void Operation::ClearRuleTemplate() {
	ClearTemplate();
	rule_template.ClearVectors();
}

void Operation::ClearTemplate() {
	fuzzy_set_template.SetGraphName("");
	fuzzy_set_template.SetXAxisName("");
	fuzzy_set_template.SetMax(0);
	fuzzy_set_template.SetMax(0);
	fuzzy_set_template.SetGraphType(0);
}

void Operation::AddSetData(const std::string & data, const int& index, const bool& has_operator, const bool&is_consequence) {
	switch (index)
	{
	case 0:
		fuzzy_set_template.SetXAxisName(data);
		break;
	case 1:
		fuzzy_set_template.SetGraphName(data);
		break;
	case 2:
		fuzzy_set_template.SetMin(std::stoi(data));
		break;
	case 3:
		fuzzy_set_template.SetMax(std::stoi(data));
		break;
	case 4:
		fuzzy_set_template.SetGraphType(std::stoi(data));
		if (is_consequence){
			fuzzy_set_template.SetSetType(0);
		}
		else {
			fuzzy_set_template.SetSetType(1);
		}
		break;
		
	case 5:
		if (has_operator) {
			fuzzy_set_template.SetOperatorValue(std::stoi(data));
		}
		break;
	}
}

const FuzzySet Operation::GetData() {
	bool whats_next=true;//false is antecedent
	bool has_operator = false;
	if (rule_vector.size()>0){

	}
	else {
		whats_next = false;
	}
	fuzzy_set_template=rule_template.GetSetValues(whats_next, has_operator);
	return fuzzy_set_template;
}