#include "GraphingTool.h"
#include <iostream>


void GraphingTool::CreatePoints(const int& index, const int& min, const int& max) {
	m_vertices.resize(100 * 100);
	sf::Vector2i size(100, 100);
	for (int y = 0; y < size.y; y++) {
		for (int x = 0; x < size.x; x++) {
			if ((x > 30 && y <= 99)) {
				if ((x < 90 && y <= 99)) {
					float temp_x = (float)x / 10.f;
					auto temp_y = GetPoint(index, min, max, temp_x);
					temp_y *= 10.f;
					float full_y = 100.f - temp_y;
					m_vertices[y * size.x + x].position = sf::Vector2f(x, full_y);
					m_vertices[y * size.x + x].color = sf::Color::Black;
					
				}
			}
		}
	}
	CleanUp();

	g.Test();
}

void GraphingTool::CleanUp() {
	sf::VertexArray temp_array;
	for (size_t y = 0; y < 100; y++){
		for (size_t x = 0; x < 100; x++){
			if (m_vertices[y * 100 + x].color == sf::Color::Black) {
				temp_array.append(m_vertices[y * 100 + x]);
			}
		}
	}
	m_vertices.clear();
	m_vertices = temp_array;
}

float GraphingTool::GetPoint(const int& index,const int& min,const int&max, const float& x) {
	float temp_y=0.0f;
	switch (index)
	{
	case 0:
		temp_y = g.TriangularFunction(min, max, x);
		break;
	case 1:
		temp_y = g.ZFunction(min, max, x);
		break;
	case 2:
		temp_y = g.SFunction(min, max, x);
		break;
	case 3:
		temp_y = g.SmoothSFunction(min, max, x);
		break;
	case 4:
		temp_y = g.SmoothZFunction(min, max, x);
		break;
	case 5:
		temp_y = g.TrapezoidalFunction(min, max, x);
		break;
	case 6:
		temp_y = g.GaussianFunction(min, max, x);
		break;
	}
	return temp_y;
}