#include "Button.h"
Button::Button(const sf::Font& font_, const sf::Vector2f& loc_, const sf::Vector2f& size_) {
	button_text.setFont(font_);
	button_shape.setSize(size_);
	button_text.setFillColor(sf::Color(0, 0, 0));
	button_shape.setFillColor(sf::Color::White);
	button_shape.setOutlineColor(sf::Color::Black);
	button_shape.setOutlineThickness(1.f);
	button_text.setCharacterSize(18);
	this->setPosition(loc_);
	
}

Button::Button() {

}

void Button::SetButtonText(const std::string& str_) {
	button_text.setString(str_);
}