#include "DescriptionInputs.h"

DescriptionInputs::DescriptionInputs():window(nullptr),is_go_back(false) {

}

DescriptionInputs::DescriptionInputs(const sf::Font& font, sf::RenderWindow* hwnd):window(hwnd),is_go_back(false){
	back_text.setFont(font);
	back_text.setFillColor(sf::Color(0, 0, 0));
	back_text.setCharacterSize(18);
	back_text.setString("Back");
	back_text.setPosition(sf::Vector2f(50, 50));

	description_text.setFont(font);
	description_text.setFillColor(sf::Color(0, 0, 0));
	description_text.setPosition(sf::Vector2f(100, 100));
	description_text.setCharacterSize(18);


	back_button.setSize(sf::Vector2f(55, 20));
	back_button.setPosition(50, 50);
	back_button.setFillColor(sf::Color::White);
	back_button.setOutlineColor(sf::Color::Black);
	back_button.setOutlineThickness(1.f);

	popup_slot.setSize(sf::Vector2f(800, 500));
	popup_slot.setPosition(50, 50);
	popup_slot.setFillColor(sf::Color::White);
	popup_slot.setOutlineColor(sf::Color::Black);
	popup_slot.setOutlineThickness(1.f);

	SetText();
	graph_slot.Init();
}
void DescriptionInputs::Render() {
	window->draw(popup_slot);
	window->draw(back_button);
	window->draw(back_text);
	window->draw(description_text);
	graph_slot.Render(*window);
}
void DescriptionInputs::Input(InputManager input_manager) {
	input_manager.ButtonBoolPress(back_button, is_go_back,0);
	
}

void DescriptionInputs::SetText() {
	std::string output_string = "First two inputs take adjective word to describe rule, example: if temp is cold\n\n Second Two inputs take range of first temp(min &max)\n\n Graph input is number from 0-6\n\n Operator input: 0(no operator), 1(OR), 2(AND)";
	description_text.setString(output_string);
}