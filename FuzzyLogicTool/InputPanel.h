#pragma once
#include <SFML/Graphics.hpp>
#include "TextFieldObject.h"
#include "InputManager.h"
#include "Operation.h"
#include "FinalGraphTool.h"

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

	void SetOperatorValues(const float& value);
	void SetDefuzzyValue(const float& value) { defuzzy_value = value; }
	void UpdateOperatorText(const std::vector<sf::Vector2f> &points);

	void ClearValues();
	const bool GetIsClear()const { return is_clear_button; }
	void SetIsClear(bool b) { is_clear_button = b; }
	void SetIsOneRule(bool b) { is_one_rule = b; }

	const bool GetIsMax()const { return is_max; }
	void UpdateText(const std::vector<Rule>& rule_vec);
	
private:

	sf::RenderWindow* window;
	std::vector<TextFieldObject> input_fields;
	std::vector<sf::Text> display_text_fields;//both enter and display for fuzzy value
	std::vector<sf::Text> operator_text_fields;
	sf::Text defuzzy_value_field;

	bool is_input_addded;
	std::vector<float> human_values;
	std::vector<float> operator_values;
	float defuzzy_value;

	sf::RectangleShape compute_button;
	sf::Text compute_text;
	bool is_done;

	FinalGraphTool graph_image;
	bool is_image_created;

	sf::Text graph_text;

	std::string cons_name;


	sf::Text clear_text;
	sf::RectangleShape clear_button;

	bool is_clear_button;

	sf::Text min_text;
	sf::RectangleShape min_button;
	sf::Text max_text;
	sf::RectangleShape max_button;
	bool is_one_rule;
	bool is_min;
	bool is_max;
};

