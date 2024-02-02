#include "GraphFunctionCalculator.h"


float GraphFunctionCalculator::TriangularFunction(const float& a, const float& c, const float& input_value) {
	//find middle
	//write out rules
	//a =min, b=midpoint, c=max
	float b = (a+ c)/2.f;
	float return_value = 0.f;
	if (input_value<=a){
		return_value = 0.f;
	}
	if (a<= input_value && input_value<=b)	{
		return_value = ((input_value - a) / (b - a));
	}
	if (b<= input_value&&input_value<=c){
		return_value = ((c- input_value) / (c - b));
	}
	if (c<=input_value){
		return_value = 0.f;
	}
	return return_value;
}