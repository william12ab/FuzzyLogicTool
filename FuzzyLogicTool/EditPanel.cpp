#include "EditPanel.h"

EditPanel::EditPanel() {

}

EditPanel::EditPanel(sf::RenderWindow* hwnd, const sf::Font& font):window(hwnd),is_edit_diplay(false){
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

	for (size_t i = 0; i < display_text_field.size(); i++){
		window->draw(display_text_field[i]);
	}
	for (size_t i = 0; i < input_text_fields.size(); i++) {
		window->draw(input_text_fields[i].GetShape());
		window->draw(input_text_fields[i].GetTextField());
	}
}
void EditPanel::Input(InputManager input_manager) {
	input_manager.ButtonBoolPress(done_button, is_done_pressed, 0);
	input_manager.ButtonBoolPress(description_button, is_load_help, 0);
}

void EditPanel::SetInfo(const int& ant_size) {
	display_text_field.resize(3 + ant_size - 1);
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

	SetInputObj(ant_size);
	SetNumericalInput(ant_size);
}

void EditPanel::SetInputObj(const int& ant_size) {
	auto temp_f = description_text.getFont();
	int size_ = (ant_size * 3) + 2;//graph name, axis name, operator(*antecedent size) + graph name, axis name for conseqeunce
	int x_pos = 100;
	int y_pos = 150;
	int loc_counter = 0;
	for (int i = 0; i < size_; i++) {
		input_text_fields.emplace_back(TextFieldObject(20, sf::Vector2f(x_pos, y_pos), *temp_f));
		x_pos += 200;
		if (loc_counter ==2){
			y_pos += 100;
			loc_counter = 0;
		}
		loc_counter++;
	}
}

void EditPanel::SetNumericalInput(const int& ant_size) {
	auto temp_f = description_text.getFont();
	int size_ = (ant_size * 3) + 2;//min max, graph value* antecedent size + min max for coonsequence
	float x_pos = 100;
	float y_pos = 400;
	int loc_counter = 0;
	for (size_t i = 0; i < size_; i++){
		input_text_fields.emplace_back(TextFieldObject(20, sf::Vector2f(x_pos, y_pos), *temp_f));
		y_pos += 100;
		if (loc_counter == 2) {
			loc_counter = 0;
			x_pos += 200;
		}
		loc_counter++;
	}
}

void EditPanel::SetAntecedentInfo(const FuzzySet& set_val,int&index) {
	
	input_text_fields[index].SetPrevious(set_val.GetxName());
	index++;
	input_text_fields[index].SetPrevious(set_val.GetGraphName());
	index++;
	if (set_val.GetOperatorValue() == 1) {
		input_text_fields[index].SetPrevious("1");//or
	}
	else if (set_val.GetOperatorValue() == 2) {
		input_text_fields[index].SetPrevious("2");//and
	}
	else {
		input_text_fields[index].SetPrevious("3");//blank
	}
	index++;
}
void EditPanel::SetAntecedentNumericalInfo(const FuzzySet& vals, int& index) {
	input_text_fields[index].SetPrevious(std::to_string(vals.GetMin()));
	index++;
	input_text_fields[index].SetPrevious(std::to_string(vals.GetMax()));
	index++;
	input_text_fields[index].SetPrevious(std::to_string(vals.GetGraphType()));
	index++;
}

void EditPanel::SetInfo(const Rule& rule_vec) {
	//set the input panels with the rule info 
	int has_op =rule_vec.GetAntecedentVector()[0].GetOperatorValue();//if not 0 then operator
	int size_antecedent = rule_vec.GetAntecedentVector().size();
	int loc_counter = 0;
	for (size_t i = 0; i < size_antecedent; i++){
		SetAntecedentInfo(rule_vec.GetAntecedentVector()[i], loc_counter);
	}
	input_text_fields[loc_counter].SetPrevious(rule_vec.GetConsequenceVector()[0].GetxName());
	loc_counter++;
	input_text_fields[loc_counter].SetPrevious(rule_vec.GetConsequenceVector()[0].GetGraphName());
	loc_counter++;
	//sets written inputs

	//numerical inputs
	for (size_t i = 0; i < size_antecedent; i++){
		SetAntecedentNumericalInfo(rule_vec.GetAntecedentVector()[i], loc_counter);
	}
	input_text_fields[loc_counter].SetPrevious(std::to_string(rule_vec.GetConsequenceVector()[0].GetMin()));
	loc_counter++;
	input_text_fields[loc_counter].SetPrevious(std::to_string(rule_vec.GetConsequenceVector()[0].GetMax()));
	loc_counter++;
}