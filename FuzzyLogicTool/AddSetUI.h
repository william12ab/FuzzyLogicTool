#pragma once
#include "TextFieldObject.h"
#include "InputManager.h"
class AddSetUI
{
public:
	AddSetUI(int num_text_fields,int num_display_text_fields, sf::RenderWindow* hwnd,const bool& e_is_second,const bool& e_is_consequence, const bool&e_is_operator, const sf::Font &font);//set positions
	AddSetUI();
	~AddSetUI();
	void SetDisplayText();
	void Render();
	void HandleInput(InputManager input_manager, sf::Event event);

	bool GetIsMoveOne() {return is_move_on;}
	bool GetIsSecond() { return is_second; }
	bool GetIsConsequence() {return is_consequence;}
	const std::string GetInfoFromTextField(const int& text_index) const;
private:

	std::vector<sf::Text> display_text_fields;
	std::vector<TextFieldObject> text_fields;
	sf::RenderWindow* window;
	sf::RectangleShape bool_shape;
	sf::RectangleShape bacK_button;
	sf::Text back_text;

	bool is_move_on;
	bool is_second;
	bool is_consequence;
	bool is_operator;

};

