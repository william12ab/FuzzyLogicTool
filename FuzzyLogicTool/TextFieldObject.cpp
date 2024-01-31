#include "TextFieldObject.h"


void TextFieldObject::ChangePositions(const sf::Vector2f& p) {
	text_field.setPosition(p);
	m_rect.setPosition(p);
}

void TextFieldObject::SubtractKey() {
	m_text = m_text.substr(0, m_text.size() - 1);
}
void TextFieldObject::Addletter(const sf::Uint32& letter) {
    if (letter!=9){
        m_text += letter;
    }
}

void TextFieldObject::SetText() {
	text_field.setString(m_text);
}

void TextFieldObject::ClearText() {
    m_text = "";
    text_field.setString(m_text);
}
void TextFieldObject::SetPrevious(std::string s) {
    m_text = s;
    SetText();
}

void TextFieldObject::SetFocus(bool focus) {
    m_hasfocus = focus;
    if (focus) {
        m_rect.setOutlineColor(sf::Color::Blue);
    }
    else {
        m_rect.setOutlineColor(sf::Color(127, 127, 127)); // Gray color
    }
}