#pragma once
#include "Input.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics.hpp>

class InputManager
{
public:
	InputManager(Input* in, sf::View* view, sf::RenderWindow* hwnd);
	~InputManager();


	void Zoom();
private:
	Input* input;
	sf::View* view_;
	sf::RenderWindow* window;

};

