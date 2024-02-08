#pragma once
#include <SFML/System/Vector2.hpp>

class GraphFunctionCalculator
{
public:
	float TriangularFunction(const float& min, const float& max, const float& input_value);

	float ZFunction(const float& min, const float& max, const float& input_value);
	float SmoothZFunction(const float& min, const float& max, const float& input_value);
	float SmoothSFunction(const float& min, const float& max, const float& input_value);
	float SFunction(const float& min, const float& max, const float& input_value);
	float TrapezoidalFunction(const float& min, const float& max, const float& input_value);

	float GaussianFunction(const float& min, const float& max, const float& input_value);

	sf::Vector2f StandardDeviation(const float& min, const float& max);
};

