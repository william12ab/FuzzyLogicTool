#pragma once
#include <vector>
#include "FuzzySet.h"
#include "GraphFunctionCalculator.h"
class MathsOperator
{
public:
	
	float CalculateFuzzyValue(const FuzzySet& set_, const float& human_input);

	bool IsOnSegment(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3);
	int FindOrientation(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3);
	bool DoIntersect(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3, const sf::Vector2f& p4);

private:
	GraphFunctionCalculator calculator;
};

