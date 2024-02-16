#pragma once
#include <SFML/Graphics.hpp>
#include "InputManager.h"
#include "Rule.h"
class EditPanel
{
public:
	EditPanel(sf::RenderWindow* hwnd, const int& size_of_rule_vector, const sf::Font& font);
	void Render();
	void Input(InputManager input_manager);
	void SetInfo(const Rule &rule_obj);
	void SetInputObj(const Rule& rule_obj);

	void SetNumericalInput(const Rule& rule_obj);

	void SetIsLoadHelp(bool b) { is_load_help = b; }
	const bool GetIsLoadHelp()const { return is_load_help; }
	const bool GetIsDonePressed()const { return is_done_pressed; }

private:
	sf::RenderWindow* window;
	sf::RectangleShape done_button;
	sf::Text done_text;

	bool is_done_pressed;
	sf::RectangleShape description_button;
	sf::Text description_text;

	bool is_load_help;

	std::vector<sf::Text> display_text_field;
	std::vector<TextFieldObject> input_text_fields;
};

