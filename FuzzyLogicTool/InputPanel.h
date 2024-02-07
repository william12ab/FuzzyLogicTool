#pragma once
#include <SFML/Graphics.hpp>
#include "TextFieldObject.h"
#include "InputManager.h"
#include "Operation.h"

class InputPanel
{
public:
	InputPanel();
	InputPanel(const int& size_of_rule_vector, const int& size_of_total_antecendents, sf::RenderWindow* hwnd, const sf::Font& font);

	void Render();
	void HandleInput(InputManager input_manger, sf::Event e);
	void SetText(const std::vector<Rule>& rule_vec);
	void CheckForInputAdded();

	const bool GetIsInputAdded() const { return is_input_addded;}
	const std::vector<float> GetHumanValues() {return human_values;}
private:

	sf::RenderWindow* window;
	std::vector<TextFieldObject> input_fields;
	std::vector<sf::Text> display_text_fields;//both enter and display for fuzzy value
	std::vector<sf::Text> operator_text_fields;
	sf::Text defuzzy_value_field;

	bool is_input_addded;
	std::vector<float> human_values;

};

