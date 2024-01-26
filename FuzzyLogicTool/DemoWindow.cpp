#include "DemoWindow.h"
#include <iostream>

void DemoWindow::CreateRule(std::string& n, FuzzySet& antecedent, Rule& new_rule, int& operator_value, Operation& new_operation) {
    GetAntecedentValues(n, antecedent, new_rule, operator_value);
    GetConsequenceValues(n, antecedent, new_rule);
    new_operation.CreateNewOperation(new_rule);
}

void DemoWindow::CreateOpertation() {
    Operation new_operation;
    FuzzySet fuzzy_set_template;
    Rule rule_template;
    int operator_value_template = 0;

    std::string n;
    CreateRule(n,fuzzy_set_template,rule_template,operator_value_template,new_operation);
}
void DemoWindow::GetAntecedentValues(std::string& n, FuzzySet& antecedent, Rule& new_rule, int operator_value) {
    std::cout << "Enter rule: if ___: ";
    std::cin >> n;
    antecedent.SetXAxisName(n);
    std::cout << " is ___: ";
    std::cin >> n;
    antecedent.SetGraphName(n);
    GetOperatorValue(n, operator_value, new_rule, antecedent);
}
void DemoWindow::GetOperatorValue(std::string& n, int& operator_value, Rule& new_rule, FuzzySet& antecedent) {
    std::cout << "Add Operator, or onto consequence: y/n ";
    std::cin >> n;
    if (n == "y") {
        std::cout << "OR/AND ";
        std::cin >> n;
        if (n == "OR") {
            operator_value = 0;
        }
        else {
            operator_value = 1;
        }
        new_rule.AddAntecedent(antecedent);
        new_rule.AddOperator(operator_value);
        GetAntecedentValues(n, antecedent, new_rule, operator_value);
    }
    else {
        new_rule.AddAntecedent(antecedent);
    }
}
void DemoWindow::GetConsequenceValues(std::string& n, FuzzySet& consequence, Rule& new_rule) {
    std::cout << "Then ___: ";
    std::cin >> n;
    consequence.SetXAxisName(n);
    std::cout << " is ___:";
    std::cin >> n;
    consequence.SetGraphName(n);
    new_rule.AddConsequence(consequence);
}