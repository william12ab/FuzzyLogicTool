#include "TextFieldObject.h"


void TextFieldObject::SubtractKey() {
	m_text = m_text.substr(0, m_text.size() - 1);
}
void TextFieldObject::Addletter(const sf::Uint32& letter) {
	m_text += letter;
}

void TextFieldObject::SetText() {
	text_field.setString(m_text);
}