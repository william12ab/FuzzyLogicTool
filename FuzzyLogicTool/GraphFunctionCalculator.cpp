#include "GraphFunctionCalculator.h"
#include <vector>


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


float GraphFunctionCalculator::ZFunction(const float& a, const float& b, const float& input_value) {
	float return_value = 0.0f;
	if (input_value< a){
		return_value = 1.0f;
	}
	if (a<= input_value && input_value<=b){
		return_value = (a - input_value) / (a - b);
	}
	if (input_value>b){
		return_value = 0;
	}
	return return_value;
}
float GraphFunctionCalculator::SFunction(const float& a, const float& b, const float& input_value) {
	float return_value=0.f;
	if (input_value<a){
		return_value = 0.f;
	}
	if (a<=input_value&& input_value<=b){
		return_value=(input_value - a) / (b - a);
	}
	if (input_value>b){
		return_value = 1.0f;
	}
	return return_value;
}

float GraphFunctionCalculator::TrapezoidalFunction(const float& a, const float& d, const float& x) {
	float midpoint = (a + d) / 2.f;
	float gap = midpoint - a;
	gap = gap / 2.f;

	float b = a+gap;
	//peak of a
	float c = d-gap;
	//peak of d
	float return_value = 0.0f;
	if (x<=a){
		return_value = 0.f;
	}
	if (a<=x && x<=b){
		return_value = (x - a) / (b - a);
	}
	if (c<=x && x<=d){
		return_value = (d - x) / (d - c);
	}
	if (d<=x){
		return_value = 0.0f;
	}
	if (b<=x&&x<=c){
		return_value = 1.0f;
	}
	return return_value;
}

float GraphFunctionCalculator::SmoothZFunction(const float& a, const float& b, const float& x) {
	float return_value = 0.0f;
	if (x<=a){
		return_value = 1.0f;
	}
	if (a<=x && x<= (a+b)/(2.f)){
		float brackets = (x - a) / (b - a);
		brackets *= brackets;
		brackets *= 2.0f;
		return_value = 1.0f - brackets;
	}
	if (((a+b)/2.f) <=x && x<=b){
		return_value = 2.f * ((x - b) / (b - a));
	}
	if (x >= b) {
		return_value = 0.0f;
	}
	return return_value;
}
float GraphFunctionCalculator::SmoothSFunction(const float& a, const float& b, const float& x) {
	float return_value = 0.0f;
	if (x <= a) {
		return_value = 0.0f;
	}
	if (a <= x && x <= (a + b) / (2.f)) {
		return_value = 2.f * ((x - b) / (b - a));
	}
	if (((a + b) / 2.f) <= x && x <= b) {
		float brackets = (x - a) / (b - a);
		brackets *= brackets;
		brackets *= 2.0f;
		return_value = 1.0f - brackets;
	}
	if (x >= b) {
		return_value = 1.0f;
	}
	return return_value;
}


sf::Vector2f GraphFunctionCalculator::StandardDeviation(const float &a, const float&b) {
	std::vector<float> arr;
	int i = 1;
	float mean = 0;
	//step 1
	arr.push_back(a);
	mean += arr[0];
	while (arr.back() < b) {
		arr.push_back(a + (i));
		mean += arr[i];
		i++;
	}
	mean /= i;

	//step 2 
	float mean_of_sq = 0;;
	for (size_t i = 0; i < arr.size(); i++) {
		mean_of_sq += (arr[i] - mean) * (arr[i] - mean);
	}
	//step 3
	mean_of_sq /= i;
	//step 4
	float s_d = sqrt(mean_of_sq);
	return sf::Vector2f(mean, s_d);
}

float GraphFunctionCalculator::GaussianFunction(const float& a, const float& b, const float& x) {
	auto components = StandardDeviation(a, b);

	float numerator = (x - components.x) * (x - components.x);
	float demoninator = 2.f * (components.y * components.y);
	float to_power = -numerator / demoninator;
	float f = exp(to_power);
	return f;
}