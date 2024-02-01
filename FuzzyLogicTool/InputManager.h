#pragma once
#include "Input.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics.hpp>
#include "TextFieldObject.h"

class InputManager
{
public:
	InputManager(Input* in, sf::View* view, sf::RenderWindow* hwnd);
	~InputManager();


	void HandleTextInput(TextFieldObject &text_object,sf::Event event, const int & index);
	void ButtonBoolPress(sf::RectangleShape& rect_shape,bool &is_move_on);
	void IsTabPressed(TextFieldObject& text_object, int& current_index,const bool&is_consequence);

	bool GetIsPressed() { return is_pressed; }
private:
	Input* input;
	sf::View* view_;
	sf::RenderWindow* window;
	bool is_pressed;
};

