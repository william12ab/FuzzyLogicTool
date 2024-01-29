#include "AddSetUI.h"
#include <iostream>

AddSetUI::AddSetUI(int num_text_fields, int num_display_text_fields, sf::RenderWindow* hwnd, const bool& e_is_second, const bool& e_is_consequence):window(hwnd), is_move_on(false){
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf"), is_second = e_is_second , is_consequence = e_is_consequence;
	for (int i = 0; i < num_text_fields; i++) {
		text_fields.push_back(TextFieldObject(20, sf::Vector2f(250.f, 200.f),font));
	}
	

	for (int i = 0; i < num_display_text_fields; i++) {
		display_text_fields.push_back(sf::Text());
		display_text_fields[i].setFont(font);
		display_text_fields[i].setFillColor(sf::Color(0, 0, 0));
		display_text_fields[i].setCharacterSize(18);
	}

	bool_shape.setSize(sf::Vector2f(45, 45));
	bool_shape.setPosition(450,400);
	bool_shape.setFillColor(sf::Color::White);
	bool_shape.setOutlineColor(sf::Color::Black);
	bool_shape.setOutlineThickness(1.f);

	bacK_button.setSize(sf::Vector2f(55, 20));
	bacK_button.setPosition(50, 50);
	bacK_button.setFillColor(sf::Color::White);
	bacK_button.setOutlineColor(sf::Color::Black);
	bacK_button.setOutlineThickness(1.f);

	back_text.setFont(font);
	back_text.setFillColor(sf::Color(0, 0, 0));
	back_text.setCharacterSize(18);
}
void AddSetUI::Render() {
	for (size_t  i = 0; i < text_fields.size(); i++){
		window->draw(text_fields[i].GetShape());
		window->draw(text_fields[i].GetTextField());
	}
	for (size_t  i = 0; i < display_text_fields.size(); i++) {
		window->draw(display_text_fields[i]);
	}
	window->draw(bool_shape);
	if (is_second){
		window->draw(bacK_button);
		window->draw(back_text);
	}
}
void AddSetUI::HandleInput(InputManager input_manager,sf::Event event) {
	for (size_t  i = 0; i < text_fields.size(); i++){
		input_manager.HandleTextInput(text_fields[i], event);
	}
	input_manager.ButtonBoolPress(bool_shape, is_move_on);
}

void AddSetUI::SetDisplayText() {
	text_fields[0].ChangePositions(sf::Vector2f(360, 200));
	text_fields[1].ChangePositions(sf::Vector2f(550, 200));
	text_fields[2].ChangePositions(sf::Vector2f(320, 250));
	text_fields[3].ChangePositions(sf::Vector2f(320, 300));
	text_fields[4].ChangePositions(sf::Vector2f(320, 350));

	if (is_consequence){
		display_text_fields[0].setString("Add consequence: if: ");
	}
	else {
		display_text_fields[0].setString("Add antecedent: if: ");
	}
	display_text_fields[0].setPosition(sf::Vector2f(200,200));
	display_text_fields[1].setString(" is: ");
	display_text_fields[1].setPosition(sf::Vector2f(520, 200));
	display_text_fields[2].setString("Min value is: ");
	display_text_fields[2].setPosition(sf::Vector2f(200, 250));
	display_text_fields[3].setString("Max value is: ");
	display_text_fields[3].setPosition(sf::Vector2f(200, 300));
	display_text_fields[4].setString("Graph type: ");
	display_text_fields[4].setPosition(sf::Vector2f(200, 350));
	display_text_fields[5].setString("Done: ");
	display_text_fields[5].setPosition(sf::Vector2f(400, 400));

	back_text.setString("Back");
	back_text.setPosition(sf::Vector2f(50, 50));
}