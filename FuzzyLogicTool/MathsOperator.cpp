#include "MathsOperator.h"

float MathsOperator::CalculateFuzzyValue(const FuzzySet& set_, const float& human_input) {
	float temp_y = 0.0f;
	switch (set_.GetGraphType())
	{
	case 0:
		temp_y = calculator.TriangularFunction(set_.GetMin(), set_.GetMax(), human_input);
		break;
	case 1:
		temp_y = calculator.ZFunction(set_.GetMin(), set_.GetMax(), human_input);
		break;
	case 2:
		temp_y = calculator.SFunction(set_.GetMin(), set_.GetMax(), human_input);
		break;
	case 3:
		temp_y = calculator.SmoothSFunction(set_.GetMin(), set_.GetMax(), human_input);
		break;
	case 4:
		temp_y = calculator.SmoothZFunction(set_.GetMin(), set_.GetMax(), human_input);
		break;
	case 5:
		temp_y = calculator.TrapezoidalFunction(set_.GetMin(), set_.GetMax(), human_input);
		break;
	case 6:
		temp_y = calculator.GaussianFunction(set_.GetMin(), set_.GetMax(), human_input);
		break;
	}
	return temp_y;
}