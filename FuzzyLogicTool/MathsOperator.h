#pragma once
#include <vector>
#include "FuzzySet.h"
#include "GraphFunctionCalculator.h"
class MathsOperator
{
public:
	
	float CalculateFuzzyValue(const FuzzySet& set_, const float& human_input);
private:
	GraphFunctionCalculator calculator;
};

