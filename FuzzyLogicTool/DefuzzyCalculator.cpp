#include "DefuzzyCalculator.h"

void DefuzzyCalculator::FindPoints(Operation new_operation) {
	sf::Vector2f first_point = sf::Vector2f(new_operation.GetRuleVector()[0].GetConsequenceVector()[0].GetMin(), 0);
	polygon_points.emplace_back(first_point);
	//point one

	//sf::Vector2f peak = FindPeak(new_operation.GetRuleVector()[0].GetConsequenceVector()[0].GetMax(), first_point.x);
	sf::Vector2f peak = sf::Vector2f(new_operation.GetRuleVector()[0].GetConsequenceVector()[0].GetPeakValue(), 1.f);


	polygon_points.emplace_back(FindEdgePoint(first_point, peak, new_operation.GetRuleVector()[0].GetOperatorValue(), 0));
	//point two

	sf::Vector2f temp_last=first_point,temp_last2=peak;
	//values for after
	MathsOperator calculator;
	if (new_operation.GetRuleVector().size() > 1) {
		int index = 1;
		if (new_operation.GetRuleVector().size() > 1) {
			index = new_operation.GetRuleVector().size() - 1;
		}
		for (size_t i = 0; i < index; i++) {
			auto p4 = sf::Vector2f(new_operation.GetRuleVector()[0].GetConsequenceVector()[0].GetMax(), 0);
			auto point_three = FindEdgePoint(p4, peak, new_operation.GetRuleVector()[i].GetOperatorValue(), 0);
			auto point_five = sf::Vector2f(new_operation.GetRuleVector()[i + 1].GetConsequenceVector()[0].GetMin(), 0);
			auto new_peak = sf::Vector2f(new_operation.GetRuleVector()[i + 1].GetConsequenceVector()[0].GetPeakValue(), 1.0f);
			auto point_six = FindEdgePoint(point_five, new_peak, new_operation.GetRuleVector()[i+1].GetOperatorValue(), 0);

			if (calculator.intersect(polygon_points[i+1], point_three, point_five, point_six)) {
				CheckForIntersection(polygon_points[i + 1], point_three, point_five, point_six);
				//addd p6 go to start of loop change bvlaues 
				polygon_points.emplace_back(point_six);
				first_point = point_six;
				peak = new_peak;
			}
			else {
				polygon_points.emplace_back(point_three);
				auto point_four = sf::Vector2f(new_operation.GetRuleVector()[i].GetConsequenceVector()[0].GetMax(), 0);
				if (calculator.intersect(point_three,point_four,point_five,point_six)){
					CheckForIntersection(point_three, point_four, point_five, point_six);
					//addd p6 go to start of loop change bvlaues 
					polygon_points.emplace_back(point_six);
					first_point = point_six;
					peak = new_peak;
				}
				else {
					//add edge, edge is now starting point
					auto edge_point= FindEdgePoint(point_three, point_four, new_operation.GetRuleVector()[i+1].GetOperatorValue(), 0);
					first_point = edge_point;
					peak = new_peak;
				}
			}
			temp_last = point_five;
			temp_last2 = new_peak;
		}
	}

	auto point_eight = sf::Vector2f(new_operation.GetRuleVector()[new_operation.GetRuleVector().size() - 1].GetConsequenceVector()[0].GetMax(), 0);
	auto point_seven = FindEdgePoint(point_eight, temp_last2, new_operation.GetRuleVector()[new_operation.GetRuleVector().size() - 1].GetOperatorValue(), 0);
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
	if (centroid.x!=0.f&&centroid.y!=0.f){
		area *= 0.5f;
		centroid /= (6.f * area);
	}
	else {
		centroid.x = polygon_points[0].x;
	}
	return centroid;
}

bool DefuzzyCalculator::CheckPoints() {
	int counter = 0;
	bool is_oob = false;
	for (size_t i = 0; i < polygon_points.size(); i++){
		if (polygon_points[i].y==0) {
			counter++;
		}
	}
	if (counter==4){
		is_oob = true;
	}
	return is_oob;
}

sf::Vector2f DefuzzyCalculator::FindMinDeFuzzyValue() {
	sf::Vector2f return_value;
	if (!CheckPoints()) {
		for (size_t i = 0; i < polygon_points.size(); i++) {
			if (polygon_points[i].y > 0) {
				return_value = polygon_points[i];
				auto comparing = polygon_points[0].x;
				comparing += return_value.x;
				comparing /= 2;
				return return_value;
			}
		}
	}
	else {
		return polygon_points[0];
	}
}

sf::Vector2f DefuzzyCalculator::FindMaxDefuzzyValue() {
	sf::Vector2f return_value;
	if (!CheckPoints()) {
		for (size_t i = (polygon_points.size() - 1); i > 0; i--) {
			if (polygon_points[i].y > 0) {
				return_value = polygon_points[i];
				auto comparing = polygon_points[3].x;
				comparing += return_value.x;
				comparing /= 2;
				TestFunction(return_value.x, comparing);
				return return_value;
			}
		}
	}
	else {
		return polygon_points[2];
	}
}


void DefuzzyCalculator::TestFunction(const float& max_value, const float& max_average) {
	float range = max_average - max_value;
	range /= 9.0f;
	float m = (polygon_points[2].y - polygon_points[3].y) / (polygon_points[2].x - polygon_points[3].x);
	float c = polygon_points[2].y - (m * polygon_points[2].x);
	

	//this is for centroid between max and average polygon shape.
	float y = m * max_average + c;
	float area = 0.0f;
	float common_factor = 0.f;
	sf::Vector2f centroid = sf::Vector2f(0.f, 0.f);
	std::vector<sf::Vector2f> new_points;
	new_points.emplace_back(polygon_points[2]);
	new_points.emplace_back(sf::Vector2f(max_average, y));
	new_points.emplace_back(sf::Vector2f(max_average, 0.f));
	new_points.emplace_back(sf::Vector2f(polygon_points[2].x, 0.f));
	for (size_t i = 0; i < new_points.size(); i++) {
		sf::Vector2f obj_one = new_points[i];
		sf::Vector2f obj_two = new_points[(i + 1) % new_points.size()];
		common_factor = (obj_one.x * obj_two.y) - (obj_two.x * obj_one.y);
		area += common_factor;
		centroid.x += (obj_one.x + obj_two.x) * common_factor;
		centroid.y += (obj_one.y + obj_two.y) * common_factor;
	}
	if (centroid.x != 0.f && centroid.y != 0.f) {
		area *= 0.5f;
		centroid /= (6.f * area);
	}

	//polygon between max and max from graph polygon shape.
	std::vector<sf::Vector2f> full_;
	full_.emplace_back(polygon_points[2]);
	full_.emplace_back(sf::Vector2f(polygon_points[2].x, 0.f));
	full_.emplace_back(polygon_points[3]);



	//this is centroid of whole shape
	area = 0.f;
	common_factor = 0.f;
	centroid = sf::Vector2f(0.f, 0.f);
	for (size_t i = 0; i < polygon_points.size(); i++) {
		sf::Vector2f obj_one = polygon_points[i];
		sf::Vector2f obj_two = polygon_points[(i + 1) % polygon_points.size()];
		common_factor = (obj_one.x * obj_two.y) - (obj_two.x * obj_one.y);
		area += common_factor;
		centroid.x += (obj_one.x + obj_two.x) * common_factor;
		centroid.y += (obj_one.y + obj_two.y) * common_factor;
	}
	if (centroid.x != 0.f && centroid.y != 0.f) {
		area *= 0.5f;
		centroid /= (6.f * area);
	}
}