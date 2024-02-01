#pragma once
#include "TextFieldObject.h"
#include "InputManager.h"
#include "FuzzySet.h"
class AddSetUI
{
public:
	AddSetUI(int num_text_fields,int num_display_text_fields, sf::RenderWindow* hwnd,const bool& e_is_second,const bool& e_is_consequence, const bool&e_is_operator, const sf::Font &font);//set positions
	AddSetUI();
	~AddSetUI();
	void SetDisplayText();
	void SetIsConsequence(bool b) { is_consequence = b;}
	void SetIsSecond(bool b) { is_second = b; }
	void SetIsoperator(bool b) { is_operator = b; }
	void SetIsOperationDone(bool b) { is_operation_done = b; }
	void SetIsFinished(bool b) { is_finished = b; }
	void SetIsLoadPanel(bool b) { is_load_panel = b; }

	void Render();
	void Update();
	void HandleInput(InputManager input_manager, sf::Event e);
	void ChangeWindowAppearance(const bool& is_second_e, const bool& is_consequence_e, const int& rule_number);
	void SetPreviousItems(FuzzySet temp, const bool& is_con_e, const bool& is_second_e, const int& rule_number);
	bool ShouldRenderButton();

	bool GetIsLoadPanel() { return is_load_panel; }
	bool GetIsMoveOne() {return is_move_on;}
	bool GetIsSecond() { return is_second; }
	bool GetIsConsequence() {return is_consequence;}
	bool GetIsOperator() { return is_operator; }
	bool GetHasOperator();
	bool GetIsGoBack() { return is_go_back; }
	bool GetIsOperationDone() { return is_operation_done;}
	bool GetIsFinished() { return is_finished; }
	const std::string GetInfoFromTextField(const int& text_index) const;
private:

	std::vector<sf::Text> display_text_fields;
	std::vector<TextFieldObject> text_fields;
	sf::RenderWindow* window;
	sf::RectangleShape bool_shape;
	sf::RectangleShape bacK_button;
	sf::RectangleShape finish_button;
	sf::RectangleShape description_button;
	sf::Text description_text;
	sf::Text back_text;
	sf::Text rule_number_text;
	sf::Text finished_text;


	bool is_load_panel;
	bool is_move_on;
	bool is_go_back;
	bool is_second;
	bool is_consequence;
	bool is_operator;
	bool has_operator;
	bool is_operation_done;
	bool is_finished;

	int current_text_field;
};

