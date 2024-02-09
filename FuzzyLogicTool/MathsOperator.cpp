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

bool MathsOperator::IsOnSegment(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3) {
	if (p2.x <= std::max(p1.x, p3.x) && p2.x >= std::min(p1.x, p3.x) &&
		p2.y <= std::max(p1.y, p3.y) && p2.y >= std::min(p1.y, p3.y))
		return true;

	return false;
	
}
int MathsOperator::FindOrientation(const sf::Vector2f& p1, const sf::Vector2f& p2, const sf::Vector2f& p3) {
	int val = (p2.y - p1.y) * (p3.x - p2.x) -
		(p2.x -p1.x) * (p3.y - p2.y);

	if (val == 0) return 0;  // collinear 

	return (val > 0) ? 1 : 2; // clock or counterclock wise 
}
bool MathsOperator::DoIntersect(const sf::Vector2f& p1, const sf::Vector2f& q1, const sf::Vector2f& p2, const sf::Vector2f& q2) {
	int o1 = FindOrientation(p1, q1, p2);
	int o2 = FindOrientation(p1, q1, q2);
	int o3 = FindOrientation(p2, q2, p1);
	int o4 = FindOrientation(p2, q2, q1);

	// General case 
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases 
	// p1, q1 and p2 are collinear and p2 lies on segment p1q1 
	if (o1 == 0 && IsOnSegment(p1, p2, q1)) return true;

	// p1, q1 and q2 are collinear and q2 lies on segment p1q1 
	if (o2 == 0 && IsOnSegment(p1, q2, q1)) return true;

	// p2, q2 and p1 are collinear and p1 lies on segment p2q2 
	if (o3 == 0 && IsOnSegment(p2, p1, q2)) return true;

	// p2, q2 and q1 are collinear and q1 lies on segment p2q2 
	if (o4 == 0 && IsOnSegment(p2, q1, q2)) return true;

	return false; // Doesn't fall in any of the above cases 
}


bool MathsOperator::ccw(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c) {
	return (c.y - a.y) * (b.x - a.x) > (b.y - a.y) * (c.x - a.x);
}
bool MathsOperator::intersect(const sf::Vector2f& a, const sf::Vector2f& b, const sf::Vector2f& c, const sf::Vector2f& d) {
	return ccw(a, c, d) != ccw(b, c, d) && ccw(a, b, c) != ccw(a, b, d);
}