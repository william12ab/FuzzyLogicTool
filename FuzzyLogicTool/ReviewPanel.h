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

	void SetIsLoadHelp(bool b) { is_load_help = b; }
	void SetText(const std::vector<Rule> &rule_vector);
	void SetSizes(const int&size);
	const bool GetIsDonePressed()const { return is_done_pressed; }
	const bool GetIsLoadHelp()const { return is_load_help; }
	void SetEditButtons(const std::vector<Rule>& rule_vector);
private:
	sf::RectangleShape done_button;
	
	sf::RenderWindow* window;

	sf::Text done_text;
	std::vector<sf::Text> rule_name_text;
	std::vector<sf::Text> rule_text_box;

	bool is_done_pressed;
	sf::RectangleShape description_button;
	sf::Text description_text;

	bool is_load_help;
	std::vector<sf::RectangleShape> edit_buttons;
	std::vector<bool> is_edit_pressed;
};

