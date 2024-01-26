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


	void HandleTextInput(TextFieldObject &text_object,sf::Event event);
	void ButtonBoolPress(sf::RectangleShape& rect_shape,bool &is_move_on);
private:
	Input* input;
	sf::View* view_;
	sf::RenderWindow* window;
	
};

