#include "GraphDisplay.h"
GraphDisplay::GraphDisplay() {
	slot.setSize(sf::Vector2f(800, 250));
	slot.setPosition(50, 300);
	slot.setFillColor(sf::Color::White);
	slot.setOutlineColor(sf::Color::Black);
	slot.setOutlineThickness(1.f);

	graphs.resize(7);
	graph_slot.resize(7);
	int temp_x = 80;
	int x_iter = 150;
	int default_y = 305;
	for (size_t i = 0; i < 7; i++){
		graph_slot[i].setSize(sf::Vector2f(120, 50));
		graph_slot[i].setPosition(temp_x, default_y);
		temp_x += x_iter;
		if (i==3){
			temp_x = 80;
			default_y += 100;
		}
		graph_slot[i].setFillColor(sf::Color::Transparent);
		graph_slot[i].setOutlineColor(sf::Color::Black);
		graph_slot[i].setOutlineThickness(1.f);

	}
	
}
void GraphDisplay::Render(sf::RenderWindow& window_) {
	window_.draw(slot);
	for (int i = 0; i < graphs.size(); i++){
		window_.draw(graph_slot[i]);
		window_.draw(graphs[i]);
	}
}
void GraphDisplay::Init() {
	//trinagle,z ,s, smooth z, smooth s, gauss, trap
	int x_addition = 150.f;
	int default_x = 20.f;
	int y_addition = 100.f;
	int default_y = 150.f;
	for (size_t i = 0; i < graphs.size(); i++){
		graphs[i].CreatePoints(i, 4, 8);

		graphs[i].setOrigin(0, 0);
		graphs[i].setPosition(default_x, default_y);
		default_x += x_addition;
		if (i==3){
			default_y += y_addition;
			default_x = 20.f;
		}
		graphs[i].setScale(2, 2);
	}
}