#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class TextFieldObject
{
public:
    TextFieldObject(unsigned int maxChars, sf::Vector2f pos, const sf::Font &f_) :
        m_size(maxChars),
        m_rect(sf::Vector2f(120, 20)), 
        m_hasfocus(false)
    {
        m_rect.setOutlineThickness(1.f);
        m_rect.setFillColor(sf::Color::White);
        m_rect.setOutlineColor(sf::Color(127, 127, 127));
        m_rect.setPosition(pos);
        
        text_field.setFont(f_);
        text_field.setString("");
        text_field.setCharacterSize(18);
        text_field.setPosition(pos);
        text_field.setFillColor(sf::Color::Black);
        is_text_added = false;
        m_text = "";
    }
    //setters
    void SetIsTextAdded(bool f) { is_text_added = f; }
    void SetText();
    void SetFocus(bool focus);
    void ClearText();
    void SetPrevious(std::string s);


    //getters
    bool GetIsTextAdded() {return is_text_added;}
    std::string GetText() const { return m_text; }
    sf::RectangleShape GetShape() { return m_rect; }
    sf::Text GetTextField() { return text_field; }
    bool GetFocus() { return m_hasfocus; }
    int GetTextSize() { return m_text.size(); }
    int GetMaxSize() { return m_size; }
    bool ifContains(sf::Vector2f point) const {return m_rect.getGlobalBounds().contains(point);}
    
    void SubtractKey();
    void Addletter(const sf::Uint32& letter);
    void ChangePositions(const sf::Vector2f &p);
private:
    unsigned int m_size;
 //   sf::Font m_font;
    std::string m_text;
    sf::RectangleShape m_rect;
    sf::Text text_field;
    bool m_hasfocus;

    bool is_text_added;
};

