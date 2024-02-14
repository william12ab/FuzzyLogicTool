#include "InputPanel.h"

InputPanel::InputPanel() :window(nullptr) {

}
InputPanel::InputPanel(const int& size_of_rule_vector, const int& size_of_total_antecendents, sf::RenderWindow* hwnd, const sf::Font& font) : window(hwnd) {
	defuzzy_value_field.setFont(font);
	defuzzy_value_field.setFillColor(sf::Color(0, 0, 0));
	defuzzy_value_field.setCharacterSize(18);
	is_input_addded = false;


	compute_button.setSize(sf::Vector2f(80, 20));
	compute_button.setPosition(500, 480);
	compute_button.setFillColor(sf::Color::White);
	compute_button.setOutlineColor(sf::Color::Black);
	compute_button.setOutlineThickness(1.f);

	compute_text.setFont(font);
	compute_text.setFillColor(sf::Color(0, 0, 0));
	compute_text.setCharacterSize(18);
	compute_text.setString("Compute");
	compute_text.setPosition(sf::Vector2f(500, 480));
	is_done = false;
	is_image_created = false;

	graph_text.setFont(font);
	graph_text.setFillColor(sf::Color(0, 0, 0));
	graph_text.setCharacterSize(18);
	graph_text.setPosition(sf::Vector2f(500, 480));
	cons_name = "";
}

void InputPanel::Render() {
	for (size_t i = 0; i < display_text_fields.size(); i++) {
		window->draw(display_text_fields[i]);
		window->draw(input_fields[i].GetShape());
		window->draw(input_fields[i].GetTextField());
	}
	for (size_t i = 0; i < operator_text_fields.size(); i++) {
		window->draw(operator_text_fields[i]);
	}
	window->draw(defuzzy_value_field);
	window->draw(compute_button);
	window->draw(compute_text);
	if (is_image_created){
		window->draw(graph_image);
		window->draw(graph_text);
	}
	
}

void InputPanel::SetText(const std::vector<Rule>& rule_vec) {
	auto temp = defuzzy_value_field.getFont();
	int total_sum = 0;
	std::vector<std::string> temp_names;
	for (size_t i = 0; i < rule_vec.size(); i++) {
		total_sum += rule_vec[i].GetAntecedentVector().size();
		for (size_t j = 0; j < rule_vec[i].GetAntecedentVector().size(); j++) {
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

	sf::Vector2f pos_ = sf::Vector2f(50, 50);
	for (size_t i = 0; i < display_text_fields.size(); i++) {
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
	for (size_t i = 0; i < operator_text_fields.size(); i++) {
		std::string display_text = "Rule Value\n after operator: ";
		operator_text_fields[i].setString(display_text);
		operator_text_fields[i].setPosition(sf::Vector2f(pos_));
		pos_.y += 50;
	}
	defuzzy_value_field.setString("Defuzzy value: ");
	defuzzy_value_field.setPosition(sf::Vector2f(500, 500));
	temp_names.clear();

	cons_name.append(rule_vec[0].GetConsequenceVector()[0].GetxName());

}

void InputPanel::HandleInput(InputManager input_manger, sf::Event e) {
	for (size_t i = 0; i < input_fields.size(); i++) {
		input_manger.HandleTextInput(input_fields[i], e, 2);
	}
	input_manger.ButtonBoolPress(compute_button, is_input_addded, 0);
}

void InputPanel::CheckForInputAdded() {
	if (is_input_addded) {
		is_done = true;
		for (size_t i = 0; i < input_fields.size(); i++) {
			human_values.push_back(std::stof(input_fields[i].GetText()));
		}
	}
}

void InputPanel::SetOperatorValues(const float& value) {
	operator_values.emplace_back(value);
}

void InputPanel::UpdateOperatorText(const std::vector<sf::Vector2f>& points_) {
	for (int i = 0; i < operator_text_fields.size(); i++) {
		std::string temp = operator_text_fields[i].getString();
		temp.append(std::to_string(operator_values[i]));
		operator_text_fields[i].setString(temp);
	}

	std::string temp_string = defuzzy_value_field.getString();
	temp_string.append(std::to_string(defuzzy_value));
	defuzzy_value_field.setString(temp_string);


	graph_image.AddPoints(points_);
	graph_image.setPosition(50, 500);
	is_image_created = true;
	graph_text.setString(cons_name);
	graph_text.setPosition(70, 500);
}