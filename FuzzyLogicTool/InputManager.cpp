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

void InputManager::ButtonBoolPress(sf::RectangleShape& rect_shape, bool& is_move_on, const int& a) {
	if (a==0){
		if (input->isMouseReleased(rect_shape, *window)) {
			is_move_on = true;
		}
	}
	else {
		if (input->isMouseReleased(rect_shape, *window)) {
			rect_shape.setFillColor(sf::Color::Black);
			is_move_on = true;
		}
		else {
			rect_shape.setFillColor(sf::Color::White);
			is_move_on = false;
		}
	}
}

void InputManager::HandleTextInput(TextFieldObject &text_object, sf::Event event, const int& index) {
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
				if (index >= 1 && index <= 5) {
					if (event.text.unicode >= 48 && event.text.unicode <= 57) {
						text_object.Addletter(event.text.unicode);
					}
				}
				if (index>=0&& index<=1){
					if (event.text.unicode>=48&& event.text.unicode<=57){
					}
					else {
						text_object.Addletter(event.text.unicode);
					}
				}
				
			}
			text_object.SetIsTextAdded(true);
			text_object.SetText();
		}
	}
}

void InputManager::IsTabPressed(TextFieldObject& text_object, int& current_index, const bool& is_consequence) {
	if (input->isKeyDown(sf::Keyboard::Tab)){
		auto pos = text_object.GetShape().getPosition();
		input->setMouseX(pos.x);
		input->setMouseY(pos.y);
		input->setKeyUp(sf::Keyboard::Tab);
		
		current_index++;
		int limit = 6;
		if (is_consequence){
			limit--;
		}
		if (current_index== limit){
			current_index = 0;
		}
		
	}
}