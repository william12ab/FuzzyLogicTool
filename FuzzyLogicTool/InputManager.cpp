#include "InputManager.h"
#include <SFML/Window/Keyboard.hpp>

InputManager::InputManager(Input* in, sf::View* view, sf::RenderWindow* hwnd) {
	input = in;
	view_ = view;
	window = hwnd;

	
}

InputManager::~InputManager() {
}

void InputManager::ButtonBoolPress(sf::RectangleShape& rect_shape, bool& is_move_on) {
	if (input->isButtonClicked(rect_shape,sf::Mouse::Left,*window)){
		rect_shape.setFillColor(sf::Color::Black);
		is_move_on = true;
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