#include "FinalGraphTool.h"

void FinalGraphTool::AddPoints(const std::vector<sf::Vector2f>& points_) {
	m_vertices.setPrimitiveType(sf::LineStrip);
	
	m_vertices.resize(points_.size() );

	for (size_t i = 0; i < points_.size(); i++){
		m_vertices[i].color = sf::Color::Black;
		m_vertices[i].position = sf::Vector2f(points_[i].x*10.f,points_[i].y*-100.f);
	}
	
}