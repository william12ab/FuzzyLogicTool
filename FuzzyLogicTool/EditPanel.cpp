#include "EditPanel.h"


EditPanel::EditPanel(sf::RenderWindow* hwnd, const int& size_of_rule_vector, const sf::Font& font):window(hwnd){
	is_done_pressed = false;
	is_load_help = false;

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

	description_text.setFont(font);
	description_text.setFillColor(sf::Color(0, 0, 0));
	description_text.setPosition(sf::Vector2f(120, 50));
	description_text.setString("Help");
	description_text.setCharacterSize(18);
	description_button.setSize(sf::Vector2f(45, 20));
	description_button.setPosition(120, 50);
	description_button.setFillColor(sf::Color::White);
	description_button.setOutlineColor(sf::Color::Black);
	description_button.setOutlineThickness(1.f);
}
void EditPanel::Render() {
	window->draw(done_button);
	window->draw(done_text);
	window->draw(description_button);
	window->draw(description_text);
}
void EditPanel::Input(InputManager input_manager) {
	input_manager.ButtonBoolPress(done_button, is_done_pressed, 0);
	input_manager.ButtonBoolPress(description_button, is_load_help, 0);
}

void EditPanel::SetInfo(const Rule& rule_obj) {
	display_text_field.resize(3 + rule_obj.GetAntecedentVector().size() - 1);
	std::string arr[3] = { "If ", "is ", "then " };
	auto temp_f=description_text.getFont();
	float x_pos = 50;
	float y_pos = 150;
	for (size_t i = 0; i < display_text_field.size(); i++){
		display_text_field[i].setFont(*temp_f);
		display_text_field[i].setFillColor(sf::Color(0, 0, 0));
		display_text_field[i].setPosition(sf::Vector2f(x_pos, y_pos));
		if (display_text_field.size()>3){
			if (i >= 3 && i < display_text_field.size()) {
				display_text_field[i].setString(arr[1]);//displays is
				x_pos = 50;
			}
			else if (i < 3) {
				display_text_field[i].setString(arr[i]);//diplays if/is
				y_pos += 100;
				x_pos += 200;
			}
			else {
				display_text_field[i].setString(arr[2]);//displays then
				y_pos += 100;
				x_pos = 50;
			}
		}
		else {
			display_text_field[i].setString(arr[i]);
		}
		display_text_field[i].setCharacterSize(18);
	}
}

void EditPanel::SetInputObj(const Rule& rule_obj) {
	auto temp_f = description_text.getFont();
	int size_ = (rule_obj.GetAntecedentVector().size() * 3) + 2;
	int x_pos = 100;
	int y_pos = 150;
	int loc_counter = 0;
	for (int i = 0; i < size_; i++) {
		input_text_fields.emplace_back(TextFieldObject(20, sf::Vector2f(x_pos, y_pos), *temp_f));
		x_pos += 200;
		if (i==2){
			y_pos += 100;
			loc_counter = 0;
		}
		loc_counter++;
	}
}

void EditPanel::SetNumericalInput(const Rule& rule_obj) {

}