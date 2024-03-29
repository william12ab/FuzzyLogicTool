#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "GraphDisplay.h"

class DescriptionInputs
{
public:
	DescriptionInputs();
	DescriptionInputs(const sf::Font& font, sf::RenderWindow* hwnd);
	
	void SetText();
	void Render();
	void Input(InputManager input_manager);

	void SetIsGoBack(bool b) { is_go_back = b; }

	bool GetIsGoBack() { return is_go_back; }

private:
	sf::RectangleShape back_button;
	sf::RectangleShape popup_slot;
	sf::Text back_text;
	sf::Text description_text;
	
	std::vector<sf::Text> graph_names_text;

	sf::RenderWindow* window;

	bool is_go_back;

	GraphDisplay graph_slot;

	bool is_panel_on;
};


