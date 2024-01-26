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


void Rule::test() {
	int a = consequence_vector.size();
	int b = consequence_vector.size();
	int c = consequence_vector.size();
}