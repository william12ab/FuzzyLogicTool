#include "FinalGraphTool.h"

void FinalGraphTool::AddPoints(const std::vector<sf::Vector2f>& points_) {
	m_vertices.setPrimitiveType(sf::Lines);
	

	auto new_points = ChangeRange(points_);
	for (size_t i = 0; i < points_.size()-1; i++){
		m_vertices.append(sf::Vertex(sf::Vector2f(new_points[i].x * 10.f, new_points[i].y * -100.f), sf::Color::Black));
		m_vertices.append(sf::Vertex(sf::Vector2f(new_points[i+1].x * 10.f, new_points[i+1].y * -100.f), sf::Color::Black));
	}
	
	m_vertices.append(sf::Vertex(sf::Vector2f(0,0), sf::Color::Black));
	m_vertices.append(sf::Vertex(sf::Vector2f(10.f*10.f, 0), sf::Color::Black));
	m_vertices.append(sf::Vertex(sf::Vector2f(0, 0), sf::Color::Black));
	m_vertices.append(sf::Vertex(sf::Vector2f(0, -10.*10.f), sf::Color::Black));
}

std::vector<sf::Vector2f> FinalGraphTool::ChangeRange(const std::vector<sf::Vector2f>& points_) {
	std::vector<float> temp_x;
	for (size_t i = 0; i < points_.size(); i++){
		temp_x.emplace_back(points_[i].x);
	}
	auto old_max=*std::max_element(temp_x.begin(), temp_x.end());
	auto old_min= *std::min_element(temp_x.begin(), temp_x.end());
	auto old_range= (old_max- old_min);
	float new_value;
	float new_range;
	float new_max = 10.f;
	float new_min = 0.f;
	new_range = (new_max - new_min);

	for (size_t i = 0; i < temp_x.size(); i++){
		temp_x[i]= (((temp_x[i] - old_min) * new_range) / old_range) + new_min;
	}
	std::vector<sf::Vector2f>new_points;
	new_points.resize(points_.size());
	for (size_t i = 0; i < new_points.size(); i++){
		new_points[i] = sf::Vector2f(temp_x[i], points_[i].y);
	}
	return new_points;
}

void FinalGraphTool::ClearGraph() {
	m_vertices.clear();
}