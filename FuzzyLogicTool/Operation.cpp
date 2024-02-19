#include "Operation.h"

Operation::Operation() {

}
Operation::~Operation() {
	if (rule_vector.size() > 0) {
		rule_vector.clear();
	}
}

void Operation::AddRule(const bool& is_consequence, int& counter_) {
	if (!is_consequence) {
		if (rule_template.GetSizeOfAntecedent() == 0){
			rule_template.AddAntecedent(fuzzy_set_template);
		}
		else if(!ValidateData(false,counter_)) {
			rule_template.ChangeInAntecedent();
			rule_template.AddAntecedent(fuzzy_set_template);
		}
	}
	else {
		if (!ValidateData(true, counter_)) {
			rule_template.AddConsequence(fuzzy_set_template);
			rule_vector.push_back(rule_template);
			ClearRuleTemplate();
		}
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
	fuzzy_set_template.SetOperatorValue(0);
}

void Operation::AddSetData(const std::string& data, const int& index, const bool& has_operator, const bool& is_consequence) {
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
		if (is_consequence) {
			fuzzy_set_template.SetSetType(0);
			fuzzy_set_template.SetGraphType(0);
		}
		else {
			fuzzy_set_template.SetSetType(1);
			fuzzy_set_template.SetGraphType(std::stoi(data));
		}
		break;

	case 5:
		if (!is_consequence) {
			if (data != "") {
				fuzzy_set_template.SetOperatorValue(std::stoi(data));
			}
			else {
				fuzzy_set_template.SetOperatorValue(0);
			}
		}
		break;
	}
}

const FuzzySet Operation::GetData(int& counter_) {
	bool whats_next = true;//false is antecedent
	bool has_operator = false;
	if (rule_vector.size() > 0) {
	}
	else {
		whats_next = false;
	}
	fuzzy_set_template = rule_template.GetSetValues(whats_next, has_operator,counter_);
	return fuzzy_set_template;
}


void Operation::PerformOperation(const std::vector<float>& defuzzy_values) {
	std::vector<float> values = defuzzy_values;
	int start_value = 0;
	int end_value = 0;
	for (int i = 0; i < rule_vector.size(); i++) {
		auto end_value = rule_vector[i].OperationWork(values);
		values.erase(values.begin() + start_value, values.begin() + end_value);
		start_value = 0;
	}
}


void swap(Rule* xp, Rule* yp) {
	Rule temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void swap(sf::Vector2f* p1, sf::Vector2f* p2) {
	sf::Vector2f temp = *p1;
	*p1 = *p2;
	*p2 = temp;
}

void Operation::ReplaceData(Rule temp_info, const int& rule_index) {
	swap(&temp_info, &rule_vector[rule_index]);
}

void Operation::SortPoints() {
	std::vector<sf::Vector2f> points;
	for (int i = 0; i < rule_vector.size(); i++) {
		points.emplace_back(rule_vector[i].GetConsequenceVector()[0].GetMin(), 0);
	}
	int min_index = 0;
	for (int i = 0; i < points.size() - 1; i++) {
		min_index = i;
		for (int j = i + 1; j < points.size(); j++)
			if (points[j].x < points[min_index].x)
				min_index = j;
		if (min_index != i)
			swap(&points[min_index], &points[i]);
		swap(&rule_vector[min_index], &rule_vector[i]);
	}
}

void Operation::AddUp(int& counter, const FuzzySet& temp_set) {
	if (temp_set.GetGraphName() == fuzzy_set_template.GetGraphName()) {
		counter++;
	}
	if (temp_set.GetxName() == fuzzy_set_template.GetxName()) {
		counter++;
	}
	if (temp_set.GetMax() == fuzzy_set_template.GetMax()) {
		counter++;
	}
	if (temp_set.GetMin() == fuzzy_set_template.GetMin()) {
		counter++;
	}
	if (temp_set.GetGraphType() == fuzzy_set_template.GetGraphType()) {
		counter++;
	}
	if (temp_set.GetOperatorValue() == fuzzy_set_template.GetOperatorValue()) {
		counter++;
	}
}

bool Operation::ValidateData(const bool& is_cons, const int& counter_) {
	bool is_duplicate = false;

	int index = 6;
	int counter = 0;
	if (is_cons) {
		index = 4;
		if (rule_template.GetConsequenceVector().size() > 0) {
			AddUp(counter, rule_template.GetConsequenceVector().back());
		}
	}
	else {
		if (rule_template.GetSizeOfAntecedent() > 0) {
			if (counter_==1){
				AddUp(counter, rule_template.GetAntecedentVector()[0]);
			}
			else {
				AddUp(counter, rule_template.GetAntecedentVector().back());
			}
		}
	}
	if (counter == index) {
		is_duplicate = true;
	}
	return is_duplicate;
}