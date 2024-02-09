#include "DefuzzyCalculator.h"





void DefuzzyCalculator::FindPoints(Operation new_operation) {
	sf::Vector2f first_point = sf::Vector2f(new_operation.GetRuleVector()[0].GetConsequenceVector()[0].GetMin(), 0);
	polygon_points.emplace_back(first_point);
	//point one

	sf::Vector2f peak = FindPeak(new_operation.GetRuleVector()[0].GetConsequenceVector()[0].GetMax(), first_point.x);

	polygon_points.emplace_back(FindEdgePoint(first_point, peak, new_operation.GetRuleVector()[0].GetOperatorValue(), 0));
	//point two

	sf::Vector2f temp_last=first_point,temp_last2=peak;

	if (new_operation.GetRuleVector().size() >1) {
		int index = 1;
		if (new_operation.GetRuleVector().size() > 1) {
			index = new_operation.GetRuleVector().size() - 1;
		}
		for (size_t i = 0; i < index; i++) {
			auto point_three = FindEdgePoint(first_point, peak, new_operation.GetRuleVector()[i].GetOperatorValue(), 1);
			sf::Vector2f point_five = sf::Vector2f(new_operation.GetRuleVector()[i + 1].GetConsequenceVector()[0].GetMin(), 0);
			peak = FindPeak(new_operation.GetRuleVector()[i + 1].GetConsequenceVector()[0].GetMax(), point_three.x);
			//point six

			if (CheckForIntersection(polygon_points[i + 1], point_three, point_five, peak)) {
			}
			else {
				polygon_points.emplace_back(point_three);
				sf::Vector2f point_four = sf::Vector2f(new_operation.GetRuleVector()[i].GetConsequenceVector()[0].GetMax(), 0);
				CheckForIntersection(point_three, point_four, point_five, peak);
			}
			auto point_six = FindEdgePoint(point_five, peak, new_operation.GetRuleVector()[i + 1].GetOperatorValue(), 0);
			polygon_points.emplace_back(point_six);
			first_point = point_five;
			//at here need to change first point and peak to new values
			temp_last = point_five;
			temp_last2 = peak;
		}
		//find p7 and p8
	}
	auto point_seven = FindEdgePoint(temp_last, temp_last2, new_operation.GetRuleVector()[new_operation.GetRuleVector().size() - 1].GetOperatorValue(), 1);
	auto point_eight = sf::Vector2f(new_operation.GetRuleVector()[new_operation.GetRuleVector().size() - 1].GetConsequenceVector()[0].GetMax(), 0);
	polygon_points.emplace_back(point_seven);
	polygon_points.emplace_back(point_eight);
}
sf::Vector2f DefuzzyCalculator::FindPeak(const float& max_, const float& x_coord) {
	auto max_p = max_;
	auto x_value = max_p - x_coord;
	x_value /= 2.f;
	x_value = x_coord + x_value;
	sf::Vector2f peak = sf::Vector2f(x_value, 1.f);
	return peak;
}

sf::Vector2f DefuzzyCalculator::FindEdgePoint(const sf::Vector2f& first_point, const sf::Vector2f& peak_point, const float& implication_value, const int& multplier_) {
	//y-y1=m(x-x1) where (x,y) y=implication from r1
	float m = (peak_point.y - first_point.y) / (peak_point.x - first_point.x);
	if (multplier_ == 1) {
		m *= -1;
	}
	float x = (implication_value - peak_point.y + (m * peak_point.x)) / m;
	sf::Vector2f point = sf::Vector2f(x, implication_value);
	return point;
}

bool DefuzzyCalculator::CheckForIntersection(const sf::Vector2f& point_one, const sf::Vector2f& point_two, const sf::Vector2f& point_three, const sf::Vector2f& point_four) {
	//y=m1x+b1
	//y=m2x+b2
	//x=(b2-b1)/(m1-m2)
	bool is_intersect;
	float m1 = (point_two.y - point_one.y) / (point_two.x - point_one.x);
	float m2 = (point_four.y - point_three.y) / (point_four.x - point_three.x);
	if (m1 != m2) {
		float b1 = point_one.y - (m1 * (point_one.x));
		float b2 = point_three.y - (m2 * (point_three.x));

		float x = (b2 - b1) / (m1 - m2);
		float y = m1 * x + b1;
		polygon_points.emplace_back(sf::Vector2f(x, y));
		is_intersect = true;
	}
	else {
		is_intersect = false;
	}
	return is_intersect;

}


sf::Vector2f DefuzzyCalculator::FindDefuzzyValue() {
	
	float area = 0.0f;
	float common_factor = 0.f;

	sf::Vector2f centroid = sf::Vector2f(0.f, 0.f);
	for (size_t i = 0; i < polygon_points.size(); i++) {
		sf::Vector2f obj_one = polygon_points[i];
		sf::Vector2f obj_two = polygon_points[(i + 1) % polygon_points.size()];
		common_factor = (obj_one.x * obj_two.y) - (obj_two.x * obj_one.y);
		area += common_factor;
		centroid.x += (obj_one.x + obj_two.x) * common_factor;
		centroid.y += (obj_one.y + obj_two.y) * common_factor;
	}
	area *= 0.5f;
	centroid /= (6.f * area);
	return centroid;
}