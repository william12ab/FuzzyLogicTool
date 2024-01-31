#include "InputManager.h"
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

InputManager::InputManager(Input* in, sf::View* view, sf::RenderWindow* hwnd) {
	input = in;
	view_ = view;
	window = hwnd;
	is_pressed = false;
}

InputManager::~InputManager() {
}

void InputManager::ButtonBoolPress(sf::RectangleShape& rect_shape, bool& is_move_on) {
	if (input->isMouseReleased(rect_shape,sf::Mouse::Left,*window,e)){
		rect_shape.setFillColor(sf::Color::Black);
		is_move_on = true;
		std::cout << "asd\n";
	}
	else {
		rect_shape.setFillColor(sf::Color::White);
		is_move_on = false;
	}
}

void InputManager::HandleTextInput(TextFieldObject &text_object, sf::Event event) {
	text_object.SetFocus(false);
	auto pos = sf::Vector2f(input->getMouseX(), input->getMouseY());

	if (text_object.ifContains(sf::Vector2f(pos))) {
		text_object.SetFocus(true);
	}
	if (text_object.GetFocus()) {
		if (event.type != sf::Event::TextEntered) {
			text_object.SetIsTextAdded(false);
		}
		else if (!text_object.GetIsTextAdded()) {
			if (event.text.unicode == 8) {
				text_object.SubtractKey();
			}
			else if (text_object.GetTextSize() < text_object.GetMaxSize()) {
				text_object.Addletter(event.text.unicode);
			}
			text_object.SetIsTextAdded(true);
			text_object.SetText();
		}
	}

}