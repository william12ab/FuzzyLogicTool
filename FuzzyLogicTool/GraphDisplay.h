#pragma once
#include "GraphingTool.h"
#include <SFML/Graphics.hpp>
class GraphDisplay
{
public:
	GraphDisplay();
	void Render(sf::RenderWindow& window_);
	void Init();
private:
	
	sf::RectangleShape slot;
	std::vector<GraphingTool> graphs;
	std::vector<sf::RectangleShape> graph_slot;
};

