#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class TextFieldObject
{
public:
    TextFieldObject(unsigned int maxChars, sf::Vector2f pos) :
        m_size(maxChars),
        m_rect(sf::Vector2f(15 * m_size, 20)), // 15 pixels per char, 20 pixels height, you can tweak
        m_hasfocus(false)
    {
        m_font.loadFromFile("C:/Windows/Fonts/Arial.ttf"); // I'm working on Windows, you can put your own font instead
        m_rect.setOutlineThickness(2);
        m_rect.setFillColor(sf::Color::White);
        m_rect.setOutlineColor(sf::Color(127, 127, 127));
        m_rect.setPosition(pos);
        
        text_field.setFont(m_font);
        text_field.setString("asdasd");
        text_field.setCharacterSize(18);
        text_field.setPosition(pos);
        text_field.setFillColor(sf::Color::Black);
        is_text_added = false;
    }
    std::string GetText() const {
        return m_text;
    }

    void SetIsTextAdded(bool f) { is_text_added = f; }
    bool GetIsTextAdded() {return is_text_added;}
    void SetText();
    bool ifContains(sf::Vector2f point) const {
        return m_rect.getGlobalBounds().contains(point);
    }
    void SetFocus(bool focus) {
        m_hasfocus = focus;
        if (focus) {
            m_rect.setOutlineColor(sf::Color::Blue);
        }
        else {
            m_rect.setOutlineColor(sf::Color(127, 127, 127)); // Gray color
        }
    }
    sf::RectangleShape GetShape() { return m_rect; }
    sf::Text GetTextField() { return text_field; }
    bool GetFocus() { return m_hasfocus; }
    void SubtractKey();
    void Addletter(const sf::Uint32& letter);
    int GetTextSize() { return m_text.size(); }
    int GetMaxSize() { return m_size; }
private:
    unsigned int m_size;
    sf::Font m_font;
    std::string m_text;
    sf::RectangleShape m_rect;
    sf::Text text_field;
    bool m_hasfocus;

    bool is_text_added;
};

