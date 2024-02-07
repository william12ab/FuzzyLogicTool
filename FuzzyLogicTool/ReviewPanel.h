#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Rule.h"

class ReviewPanel
{
public:
	ReviewPanel();
	ReviewPanel(sf::RenderWindow* hwnd, const int& size_of_rule_vector,const sf::Font &font);
	void Render();
	void Input(InputManager input_manager);

	void SetText(const std::vector<Rule> &rule_vector);
	void SetSizes(const int&size);
	const bool GetIsDonePressed()const { return is_done_pressed; }
private:
	sf::RectangleShape done_button;
	
	sf::RenderWindow* window;

	sf::Text done_text;
	std::vector<sf::Text> rule_name_text;
	std::vector<sf::Text> rule_text_box;

	bool is_done_pressed;
};

