#include "Operation.h"

Operation::Operation() {

}
Operation::~Operation() {
	if (rule_vector.size()>0){
		rule_vector.clear();
	}
}

void Operation::CreateNewOperation(Rule new_rule) {
	rule_vector.push_back(new_rule);
}