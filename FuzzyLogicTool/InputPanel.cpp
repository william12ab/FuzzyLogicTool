#include "InputPanel.h"

InputPanel::InputPanel():window(nullptr) {

}
InputPanel::InputPanel(const int& size_of_rule_vector, const int& size_of_total_antecendents,sf::RenderWindow* hwnd, const sf::Font& font):window(hwnd){
	defuzzy_value_field.setFont(font);
	defuzzy_value_field.setFillColor(sf::Color(0, 0, 0));
	defuzzy_value_field.setCharacterSize(18);
	is_input_addded = false;
}

void InputPanel::Render() {
	for (size_t i = 0; i < display_text_fields.size(); i++){
		window->draw(display_text_fields[i]);
		window->draw(input_fields[i].GetShape());
		window->draw(input_fields[i].GetTextField());
	}
	for (size_t i = 0; i < operator_text_fields.size(); i++){
		window->draw(operator_text_fields[i]);
	}
	window->draw(defuzzy_value_field);
}

void InputPanel::SetText(const std::vector<Rule>& rule_vec) {
	auto temp = defuzzy_value_field.getFont();
	int total_sum = 0;
	std::vector<std::string> temp_names;
	for (size_t i = 0; i < rule_vec.size(); i++) {
		total_sum += rule_vec[i].GetAntecedentVector().size();
		for (size_t j = 0; j < rule_vec[i].GetAntecedentVector().size(); j++){
			temp_names.push_back(rule_vec[i].GetAntecedentVector()[j].GetxName());
		}
	}
	for (size_t i = 0; i < total_sum; i++) {
		display_text_fields.push_back(sf::Text());
		display_text_fields[i].setFont(*temp);
		display_text_fields[i].setFillColor(sf::Color(0, 0, 0));
		display_text_fields[i].setCharacterSize(18);
		input_fields.push_back(TextFieldObject(20, sf::Vector2f(250.f, 200.f), *temp));
	}
	for (size_t i = 0; i < rule_vec.size(); i++) {
		operator_text_fields.push_back(sf::Text());
		operator_text_fields[i].setFont(*temp);
		operator_text_fields[i].setFillColor(sf::Color(0, 0, 0));
		operator_text_fields[i].setCharacterSize(18);
	}

	sf::Vector2f pos_=sf::Vector2f(50,50);
	for (size_t i = 0; i < display_text_fields.size(); i++){
		pos_.x = 50;
		std::string diplsay_text = "Enter value for ";
		diplsay_text.append(temp_names[i]);
		diplsay_text.append(" : ");
		display_text_fields[i].setString(diplsay_text);
		display_text_fields[i].setPosition(sf::Vector2f(pos_));
		pos_.x += 200;
		input_fields[i].ChangePositions(sf::Vector2f(pos_));
		pos_.y += 50;
	}
	pos_ = sf::Vector2f(500, 50);
	for (size_t i = 0; i <  operator_text_fields.size(); i++){
		std::string display_text = "Rule Value\n after operator: ";
		operator_text_fields[i].setString(display_text);
		operator_text_fields[i].setPosition(sf::Vector2f(pos_));
		pos_.y += 50;
	}
	defuzzy_value_field.setString("Defuzzy value: ");
	defuzzy_value_field.setPosition(sf::Vector2f(500,500));
	temp_names.clear();
}

void InputPanel::HandleInput(InputManager input_manger, sf::Event e) {
	for (size_t i = 0; i < input_fields.size(); i++) {
		input_manger.HandleTextInput(input_fields[i], e, 2);
	}
}

void InputPanel::CheckForInputAdded() {
	int counter = 0;
	for (int i = 0; i < input_fields.size(); i++) {
		if (input_fields[i].GetText() != "") {
			counter++;
		}
	}
	if (counter >= input_fields.size()) {
		if (!is_input_addded){
			is_input_addded = true;
			for (size_t i = 0; i < input_fields.size(); i++) {
				human_values.push_back(std::stof(input_fields[i].GetText()));
			}
		}
	}
}

void InputPanel::SetOperatorValues(const float& value) {
	operator_values.emplace_back(value);
}

void InputPanel::UpdateOperatorText() {
	for (int i = 0; i < operator_text_fields.size(); i++){
		std::string temp= operator_text_fields[i].getString();
		temp.append(std::to_string(operator_values[i]));
		operator_text_fields[i].setString(temp);
	}
}