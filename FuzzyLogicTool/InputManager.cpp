#include "InputManager.h"
#include <SFML/Window/Keyboard.hpp>

InputManager::InputManager(Input* in, sf::View* view, sf::RenderWindow* hwnd) {
	input = in;
	view_ = view;
	window = hwnd;
}

InputManager::~InputManager() {
}