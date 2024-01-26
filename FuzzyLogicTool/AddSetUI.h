#pragma once
#include "TextFieldObject.h"
#include "InputManager.h"
class AddSetUI
{
public:
	AddSetUI(int num_text_fields,int num_display_text_fields, sf::RenderWindow* hwnd);//set positions

	void SetDisplayText();
	void Render();
	void HandleInput(InputManager input_manager, sf::Event event);
private:

	std::vector<sf::Text> display_text_fields;
	std::vector<TextFieldObject> text_fields;
	sf::RenderWindow* window;
	sf::RectangleShape bool_shape;

	sf::Font font;
	bool is_move_on;
};

