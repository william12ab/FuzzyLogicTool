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


	bool ccw(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c);
	bool intersect(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, const sf::Vector2f& d);

private:
	GraphFunctionCalculator calculator;
};

