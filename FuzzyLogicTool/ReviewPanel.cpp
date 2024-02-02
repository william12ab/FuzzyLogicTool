#include "ReviewPanel.h"


ReviewPanel::ReviewPanel():window(nullptr) {

}

ReviewPanel::ReviewPanel(sf::RenderWindow* hwnd, const int& size_of_rule_vector, const sf::Font&font):window(hwnd) {
	rule_name_text.resize(size_of_rule_vector);
	rule_text_box.resize(size_of_rule_vector);
	for (int i = 0; i < rule_name_text.size(); i++){
		rule_text_box[i].setFont(font);
		rule_text_box[i].setFillColor(sf::Color(0, 0, 0));
		
		rule_text_box[i].setCharacterSize(18);
		rule_name_text[i].setFont(font);
		rule_name_text[i].setFillColor(sf::Color(0, 0, 0));
		
		rule_name_text[i].setCharacterSize(18);
	}

	done_button.setSize(sf::Vector2f(55, 20));
	done_button.setPosition(600, 400);
	done_button.setFillColor(sf::Color::White);
	done_button.setOutlineColor(sf::Color::Black);
	done_button.setOutlineThickness(1.f);

	done_text.setCharacterSize(18);
	done_text.setFont(font);
	done_text.setFillColor(sf::Color(0, 0, 0));
	done_text.setPosition(sf::Vector2f(600, 400));
	done_text.setString("Done");
}

void ReviewPanel::SetSizes(const int& size) {
	rule_name_text.resize(size);
	rule_text_box.resize(size);
	auto temp = rule_text_box[0].getFont();
	for (int i = 0; i < rule_name_text.size(); i++) {
		rule_text_box[i].setFont(*temp);
		rule_text_box[i].setFillColor(sf::Color(0, 0, 0));
		rule_text_box[i].setCharacterSize(18);
		rule_name_text[i].setFont(*temp);
		rule_name_text[i].setFillColor(sf::Color(0, 0, 0));
		rule_name_text[i].setCharacterSize(18);
	}
}

void ReviewPanel::SetText(const std::vector<Rule>& rule_vector) {
	SetSizes(rule_vector.size());
	for (int i = 0; i < rule_name_text.size(); i++){
		rule_name_text[i].setString("Rule: " + std::to_string(i));
		rule_name_text[i].setPosition(sf::Vector2f(100, 0));
	}
	for (int i = 0; i < rule_vector.size(); i++){
		std::string full_string = "If ";
		for (int j = 0; j < rule_vector[0].GetAntecedentVector().size();j++) {
			full_string.append(rule_vector[i].GetAntecedentVector()[j].GetxName());
			full_string.append(" is ");
			full_string.append(rule_vector[i].GetAntecedentVector()[j].GetGraphName());
			if (rule_vector[i].GetAntecedentVector()[j].GetOperatorValue()!=0){
				if (rule_vector[i].GetAntecedentVector()[j].GetOperatorValue() == 1) {
					full_string.append("\nOR ");
				}
				else {
					full_string.append("\nAND ");
				}
			}
		}
		full_string.append("\nThen ");
		full_string.append(rule_vector[i].GetConsequenceVector()[0].GetxName());
		full_string.append(" is ");
		full_string.append(rule_vector[i].GetConsequenceVector()[0].GetGraphName());

		rule_text_box[i].setString(full_string);
		rule_text_box[i].setPosition(sf::Vector2f(200, 0));
		
	}
}

void ReviewPanel::Render() {
	for (int i = 0; i < rule_name_text.size(); i++){
		window->draw(rule_name_text[i]);
		window->draw(rule_text_box[i]);
	}
	window->draw(done_button);
	window->draw(done_text);

}
void ReviewPanel::Input(InputManager input_manager) {

}