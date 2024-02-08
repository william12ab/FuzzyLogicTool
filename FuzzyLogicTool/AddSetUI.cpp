#include "AddSetUI.h"
#include <iostream>


AddSetUI::AddSetUI() :is_consequence(false), is_move_on(false), is_second(false), is_operator(true), window(nullptr), has_operator(false), is_go_back(false), is_finished(false),is_load_panel(false),is_operation_done(false) {
}
AddSetUI::~AddSetUI() {

}
AddSetUI::AddSetUI(int num_text_fields, int num_display_text_fields, sf::RenderWindow* hwnd, const bool& e_is_second, const bool& e_is_consequence, const bool& e_is_operator, const sf::Font& font):window(hwnd), is_move_on(false), has_operator(false), is_go_back(false),is_finished(false), is_load_panel(false), is_operation_done(false) {
	is_second = e_is_second , is_consequence = e_is_consequence, is_operator=e_is_operator;
	is_operation_done = false;
	is_finished = false;
	is_trigger_finished = false;
	for (int i = 0; i < num_text_fields; i++) {
		text_fields.push_back(TextFieldObject(20, sf::Vector2f(250.f, 200.f),font));
	}
	for (int i = 0; i < num_display_text_fields; i++) {
		display_text_fields.push_back(sf::Text());
		display_text_fields[i].setFont(font);
		display_text_fields[i].setFillColor(sf::Color(0, 0, 0));
		display_text_fields[i].setCharacterSize(18);
	}

	bool_shape.setSize(sf::Vector2f(45, 45));
	bool_shape.setPosition(600,400);
	bool_shape.setFillColor(sf::Color::White);
	bool_shape.setOutlineColor(sf::Color::Black);
	bool_shape.setOutlineThickness(1.f);
	description_button.setSize(sf::Vector2f(45, 20));
	description_button.setPosition(120, 50);
	description_button.setFillColor(sf::Color::White);
	description_button.setOutlineColor(sf::Color::Black);
	description_button.setOutlineThickness(1.f);

	finish_button.setSize(sf::Vector2f(45, 45));
	finish_button.setPosition(600, 450);
	finish_button.setFillColor(sf::Color::White);
	finish_button.setOutlineColor(sf::Color::Black);
	finish_button.setOutlineThickness(1.f);

	bacK_button.setSize(sf::Vector2f(55, 20));
	bacK_button.setPosition(50, 50);
	bacK_button.setFillColor(sf::Color::White);
	bacK_button.setOutlineColor(sf::Color::Black);
	bacK_button.setOutlineThickness(1.f);

	back_text.setFont(font);
	back_text.setFillColor(sf::Color(0, 0, 0));
	back_text.setCharacterSize(18);

	description_text.setFont(font);
	description_text.setFillColor(sf::Color(0, 0, 0));
	description_text.setPosition(sf::Vector2f(120, 50));
	description_text.setString("Help");
	description_text.setCharacterSize(18);


	finished_text.setFont(font);
	finished_text.setFillColor(sf::Color(0, 0, 0));
	finished_text.setPosition(sf::Vector2f(520, 450));
	finished_text.setString("Finished:");
	finished_text.setCharacterSize(18);

	rule_number_text.setFont(font);
	rule_number_text.setFillColor(sf::Color(0, 0, 0));
	rule_number_text.setPosition(sf::Vector2f(200, 50));
	rule_number_text.setString("Rule: 0" );
	rule_number_text.setCharacterSize(18);

	current_text_field = 0;
}
void AddSetUI::Render() {
	int loop_index = text_fields.size();
	int loop_index_two = display_text_fields.size();
	if (is_consequence) {
		loop_index -= 1;
		loop_index_two -= 1;
	}
	for (size_t  i = 0; i < loop_index; i++){
		window->draw(text_fields[i].GetShape());
		window->draw(text_fields[i].GetTextField());
	}
	for (size_t  i = 0; i < loop_index_two; i++) {
		window->draw(display_text_fields[i]);
	}
	if (ShouldRenderButton()){
		window->draw(bool_shape);
		if (is_consequence){
			window->draw(finish_button);
			window->draw(finished_text);
		}
	}
	if (is_second){
		window->draw(bacK_button);
		window->draw(back_text);
	}
	window->draw(description_button);
	window->draw(description_text);
	window->draw(rule_number_text);
}
void AddSetUI::Update() {
	if (!is_consequence){
		if (text_fields[5].GetText()=="") {
			has_operator = false;
		}
		else {
			has_operator = true;
		}
	}
}

void AddSetUI::SetPreviousItems(FuzzySet temp, const bool&is_con_e, const bool&is_second_e, const int& rule_number) {
	if (is_go_back){
		ChangeWindowAppearance(is_second_e,is_con_e, rule_number);
		text_fields[0].SetPrevious(temp.GetxName());
		text_fields[1].SetPrevious(temp.GetGraphName());
		text_fields[2].SetPrevious(std::to_string(temp.GetMin()));
		text_fields[3].SetPrevious(std::to_string(temp.GetMax()));
		text_fields[4].SetPrevious(std::to_string(temp.GetGraphType()));
		if (!is_con_e){
			text_fields[5].SetPrevious(std::to_string(temp.GetOperatorValue()));
		}
		is_go_back = false;
	}
}

void AddSetUI::HandleInput(InputManager input_manager,sf::Event e) {
	for (size_t  i = 0; i < text_fields.size(); i++){
		input_manager.HandleTextInput(text_fields[i], e,i);
	}
	if (is_second){
		input_manager.ButtonBoolPress(bacK_button, is_go_back,1);
	}
	if (ShouldRenderButton()){
		input_manager.ButtonBoolPress(bool_shape, is_move_on,1);
		if (is_move_on &&is_consequence){
			is_operation_done = true;
		}
		if (is_consequence){
			input_manager.ButtonBoolPress(finish_button, is_trigger_finished,1);
		}
	}
	input_manager.ButtonBoolPress(description_button, is_load_panel,0);

	input_manager.IsTabPressed(text_fields[current_text_field],current_text_field,is_consequence);
	//crashes here when current_text_field is 6
}

void AddSetUI::SetDisplayText() {
	if (is_consequence){
		text_fields[0].ChangePositions(sf::Vector2f(410, 200));
		text_fields[1].ChangePositions(sf::Vector2f(590, 200));
	}
	else {
		text_fields[0].ChangePositions(sf::Vector2f(360, 200));
		text_fields[1].ChangePositions(sf::Vector2f(550, 200));
	}
	
	text_fields[2].ChangePositions(sf::Vector2f(320, 250));
	text_fields[3].ChangePositions(sf::Vector2f(320, 300));
	text_fields[4].ChangePositions(sf::Vector2f(320, 350));
	
	if (is_operator){
		text_fields[5].ChangePositions(sf::Vector2f(320, 400));
		display_text_fields[6].setString("Operator: ");
		display_text_fields[6].setPosition(sf::Vector2f(200, 400));
	}

	if (is_consequence){
		display_text_fields[0].setString("Add consequence: Then: ");
		display_text_fields[1].setString(" is: ");
		display_text_fields[1].setPosition(sf::Vector2f(560, 200));
	}
	else {
		display_text_fields[0].setString("Add antecedent: If: ");
		display_text_fields[1].setString(" is: ");
		display_text_fields[1].setPosition(sf::Vector2f(520, 200));
	}
	display_text_fields[0].setPosition(sf::Vector2f(200,200));
	
	display_text_fields[2].setString("Min value is: ");
	display_text_fields[2].setPosition(sf::Vector2f(200, 250));
	display_text_fields[3].setString("Max value is: ");
	display_text_fields[3].setPosition(sf::Vector2f(200, 300));
	display_text_fields[4].setString("Graph type: ");
	display_text_fields[4].setPosition(sf::Vector2f(200, 350));
	if (is_consequence){
		display_text_fields[5].setString("Add new:");
		display_text_fields[5].setPosition(sf::Vector2f(500, 400));
	}
	else {
		display_text_fields[5].setString("Done:");
		display_text_fields[5].setPosition(sf::Vector2f(550, 400));
	}
	back_text.setString("Back");
	back_text.setPosition(sf::Vector2f(50, 50));
}

const std::string AddSetUI::GetInfoFromTextField(const int& text_index)const {
	return text_fields[text_index].GetText();
}

bool AddSetUI::ShouldRenderButton() {
	bool is_written = false;
	int counter = 0;
	for (int i = 0; i < 5; i++){
		if (text_fields[i].GetText()!=""){
			counter++;
		}
	}
	if (counter>=5){
		is_written = true;
	}
	return is_written;
}

void AddSetUI::ChangeWindowAppearance(const bool& is_second_e, const bool& is_consequence_e,const int& rule_number) {
	is_second = is_second_e;
	is_consequence = is_consequence_e;
	is_move_on = false;
	has_operator = false;
	is_operator = !is_consequence_e;
	for (int i = 0; i < text_fields.size(); i++){
		text_fields[i].ClearText();
	}
	SetDisplayText();
	rule_number_text.setPosition(sf::Vector2f(200, 50));
	rule_number_text.setString("Rule: " + std::to_string(rule_number));
}

bool AddSetUI::GetHasOperator() {
	if (text_fields[5].GetText() != ""&& text_fields[5].GetText() != "0"){
		return true;
	}
	else {
		return false;
	}
}