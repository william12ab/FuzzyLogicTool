#include "EditPanel.h"

EditPanel::EditPanel() {

}

EditPanel::EditPanel(sf::RenderWindow* hwnd, const sf::Font& font):window(hwnd),is_edit_diplay(false){
	is_done_pressed = false;
	is_load_help = false;

	done_button.setSize(sf::Vector2f(55, 20));
	done_button.setPosition(600, 500);
	done_button.setFillColor(sf::Color::White);
	done_button.setOutlineColor(sf::Color::Black);
	done_button.setOutlineThickness(1.f);

	done_text.setCharacterSize(18);
	done_text.setFont(font);
	done_text.setFillColor(sf::Color(0, 0, 0));
	done_text.setPosition(sf::Vector2f(600, 500));
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
void EditPanel::Input(InputManager input_manager,sf::Event e) {
	input_manager.ButtonBoolPress(done_button, is_done_pressed, 0);
	input_manager.ButtonBoolPress(description_button, is_load_help, 0);
	for (size_t i = 0; i < input_text_fields.size(); i++) {
		input_manager.HandleTextInput(input_text_fields[i], e);
	}
}

void EditPanel::SetInfo(const int& ant_size) {
	display_text_field.resize(4+(ant_size-1));
	std::string arr[3] = { "If ", "is ", "then " };
	auto temp_f=description_text.getFont();
	float x_pos = 50;
	float y_pos = 75;
	float x_add = 200;
	int local_index = 0;
	for (size_t i = 0; i < display_text_field.size(); i++){
		display_text_field[i].setFont(*temp_f);
		display_text_field[i].setFillColor(sf::Color(0, 0, 0));

		if (display_text_field.size()>4){
			if (local_index == 1) {
				display_text_field[i].setString(arr[1]);//diplays is
				
				if (i==display_text_field.size()-2){
					local_index = 2;
				}
				if (i>1){
					y_pos += 50;
				}
				else {
					x_pos += x_add;
				}
			}
			else if (local_index > 1) {
				display_text_field[i].setString(arr[2]);//displays then
				y_pos -= 50;
				x_pos += (x_add*2);
				local_index = 1;
			}
			if (local_index == 0) {
				display_text_field[i].setString(arr[0]);
				local_index++;
			}
			display_text_field[i].setPosition(sf::Vector2f(x_pos, y_pos));
			if (display_text_field[i].getString() == arr[2]) {
				y_pos += 50;
				x_pos = 50;
			}
		}
		else {
			if (local_index ==1) {
				display_text_field[i].setString(arr[1]);//displays is
				x_pos += x_add;
				local_index++;
			}
			else if(local_index>1){
				display_text_field[i].setString(arr[2]);//displays then
				//y_pos += 50;
				x_pos += (x_add * 2);
				local_index = 1;
			}
			if (local_index == 0) {
				display_text_field[i].setString(arr[0]);
				local_index++;
			}
			display_text_field[i].setPosition(sf::Vector2f(x_pos, y_pos));
			if (display_text_field[i].getString()==arr[2]){
				y_pos += 50;
				x_pos = 50;
			}
		}
		display_text_field[i].setCharacterSize(18);
	}
	SetInputObj(ant_size);
	SetNumericalInput(ant_size);
}

void EditPanel::SetInputObj(const int& ant_size) {
	auto temp_f = description_text.getFont();
	int size_ = (ant_size * 3) + 2;//graph name, axis name, operator(*antecedent size) + graph name, axis name for conseqeunce
	int x_pos = 90;
	int y_pos = 75;
	int loc_counter = 0;
	float x_add = 175;
	for (int i = 0; i < size_; i++) {
		input_text_fields.emplace_back(TextFieldObject(20, sf::Vector2f(x_pos, y_pos), *temp_f));
		x_pos += x_add;
		loc_counter++;
		if (loc_counter ==3){
			y_pos += 50;
			loc_counter = 0;
			x_pos = 90;
		}
	}
}

void EditPanel::SetNumericalInput(const int& ant_size) {
	auto temp_f = description_text.getFont();
	int size_ = (ant_size * 3) + 2;//min max, graph value* antecedent size + min max for coonsequence
	float x_pos = 50;
	float y_pos = 400;
	int loc_counter = 0;
	for (size_t i = 0; i < size_; i++){
		input_text_fields.emplace_back(TextFieldObject(20, sf::Vector2f(x_pos, y_pos), *temp_f));
		y_pos += 50;
		loc_counter++;
		if (loc_counter == 3) {
			loc_counter = 0;
			x_pos += 175;
			y_pos = 400;
		}
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
		input_text_fields[index].SetPrevious("not editable");//blank
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

bool EditPanel::CompareInfo(const Rule& temp_rule, Rule& temp_holder) {
	int size_antecedent = temp_rule.GetAntecedentVector().size();
	bool is_different = false;
	int local_counter = 0;
	int antecedent_index=0;
	std::vector<FuzzySet> temp_set;
	
	for (local_counter = 0; local_counter < size_antecedent; local_counter+=8){
		temp_set.emplace_back();
		temp_set.back().SetSetType(1);
		temp_set[antecedent_index].SetXAxisName(input_text_fields[local_counter].GetText());
		temp_set[antecedent_index].SetXAxisName(input_text_fields[local_counter + 1].GetText());
		if (input_text_fields[local_counter + 2].GetText()!="not editable"){
			temp_set[antecedent_index].SetOperatorValue(std::stof(input_text_fields[local_counter + 2].GetText()));
		}
		else {
			temp_set[antecedent_index].SetOperatorValue(0);
		}
		
		temp_set[antecedent_index].SetMin(std::stof(input_text_fields[local_counter + 5].GetText()));
		temp_set[antecedent_index].SetMax(std::stof(input_text_fields[local_counter + 6].GetText()));
		temp_set[antecedent_index].SetGraphType(std::stof(input_text_fields[local_counter + 7].GetText()));
		if (input_text_fields[local_counter].GetText()!=temp_rule.GetAntecedentVector()[antecedent_index].GetxName()){
			is_different = true;
		}
		if (input_text_fields[local_counter +1].GetText() != temp_rule.GetAntecedentVector()[antecedent_index].GetGraphName()) {
			is_different = true;
		}
		if (input_text_fields[local_counter + 2].GetText() != std::to_string(temp_rule.GetAntecedentVector()[antecedent_index].GetOperatorValue())) {
			is_different = true;
		}
		if (input_text_fields[local_counter + 5].GetText() != std::to_string(temp_rule.GetAntecedentVector()[antecedent_index].GetMin())) {
			is_different = true;
		}
		if (input_text_fields[local_counter + 6].GetText() != std::to_string(temp_rule.GetAntecedentVector()[antecedent_index].GetMax())) {
			is_different = true;
		}
		if (input_text_fields[local_counter + 7].GetText() != std::to_string(temp_rule.GetAntecedentVector()[antecedent_index].GetGraphType())) {
			is_different = true;
		}
		antecedent_index++;
	}
	temp_set.emplace_back();
	temp_set.back().SetSetType(0);
	temp_set[temp_set.size() - 1].SetXAxisName(input_text_fields[(3 * size_antecedent)].GetText());
	temp_set[temp_set.size() - 1].SetGraphName(input_text_fields[(3 * size_antecedent) + 1].GetText());
	temp_set[temp_set.size() - 1].SetMin(std::stof(input_text_fields[local_counter].GetText()));
	temp_set[temp_set.size() - 1].SetMax(std::stof(input_text_fields[local_counter + 1].GetText()));
	if (input_text_fields[(3*size_antecedent)].GetText() != temp_rule.GetConsequenceVector()[0].GetxName()) {
		is_different = true;
	}
	if (input_text_fields[(3 * size_antecedent) +1].GetText() != temp_rule.GetConsequenceVector()[0].GetGraphName()) {
		is_different = true;
	}
	if (input_text_fields[local_counter].GetText() != std::to_string(temp_rule.GetConsequenceVector()[0].GetMin())) {
		is_different = true;
	}
	if (input_text_fields[local_counter+1].GetText() != std::to_string(temp_rule.GetConsequenceVector()[0].GetMax())) {
		is_different = true;
	}
	if (is_different){
		for (size_t i = 0; i < antecedent_index; i++){
			temp_holder.AddAntecedent(temp_set[i]);
		}
		temp_holder.AddConsequence(temp_set.back());
	}
	return is_different;
}