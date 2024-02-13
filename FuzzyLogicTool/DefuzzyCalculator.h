#pragma once
#include <SFML/Graphics.hpp>
#include "Operation.h"
#include "MathsOperator.h"
#include "FinalGraphTool.h"

class DefuzzyCalculator
{
public:
	void FindPoints(Operation new_operation);
	sf::Vector2f FindEdgePoint(const sf::Vector2f& first_point, const sf::Vector2f& peak_point, const float& implication_value, const int& multplier_);
	sf::Vector2f FindPeak(const float& max_, const float& x_coord);
	bool CheckForIntersection(const sf::Vector2f& point_one, const sf::Vector2f& point_two, const sf::Vector2f& point_three, const sf::Vector2f& point_four);

	sf::Vector2f FindDefuzzyValue();

	const std::vector<sf::Vector2f> GetPoints() const{ return polygon_points; }

private:

	std::vector<sf::Vector2f> polygon_points;
	
};

