#include "Operation.h"

Operation::Operation() {

}
Operation::~Operation() {
	if (rule_vector.size()>0){
		rule_vector.clear();
	}
}

void Operation::AddRule(const bool& is_antecedent) {
	if (is_antecedent) {
		rule_template.AddAntecedent(fuzzy_set_template);
	}
	else {
		rule_template.AddConsequence(fuzzy_set_template);
		rule_vector.push_back(rule_template);
	}
	ClearTemplate();
}

void Operation::ClearTemplate() {
	fuzzy_set_template.SetGraphName("");
	fuzzy_set_template.SetXAxisName("");
	fuzzy_set_template.SetMax(0);
	fuzzy_set_template.SetMax(0);
	fuzzy_set_template.SetGraphType(0);
}

void Operation::AddSetData(const std::string & data, const int& index, const bool& has_operator) {
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
		break;
		
	case 5:
		if (has_operator) {
			rule_template.AddOperator(std::stoi(data));
		}
		break;
	}
}