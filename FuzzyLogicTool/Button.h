#pragma once
#include <SFML/Graphics.hpp>
class Button: public sf::Drawable, public sf::Transformable
{
public:
    Button(const sf::Font& font_, const sf::Vector2f &loc_, const sf::Vector2f& size_);
    Button();
    void SetButtonText(const std::string &str_);

protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // apply the entity's transform -- combine it with the one that was passed by the caller
        states.transform *= getTransform(); // getTransform() is defined by sf::Transformable
        // you may also override states.shader or states.blendMode if you want
        // draw the vertex array
        target.draw(button_shape, states);
        target.draw(button_text, states);
    }
private:

	sf::RectangleShape button_shape;
	sf::Text button_text;
};

