#include "LogicHandler.h"
#include <iostream>
LogicHandler::LogicHandler(sf::RenderWindow* window, const sf::Font& font) {
	AddSetUI* temp = new AddSetUI(6, 7, window, false, false, true, font);
	window_template = *temp;
	
	window_template.SetDisplayText();
	is_added = false;
	DescriptionInputs *temphelp = new DescriptionInputs(font, window);
	help_panel = *temphelp;

	delete temp;
	temp = NULL;
	delete temphelp;
	temphelp = NULL;
}
void LogicHandler::Update() {
	window_template.Update();
	//displaying old info page
	if (window_template.GetIsGoBack()) {
		auto temp = new_operation.GetData();
		if (temp.GetSetType() == 0) {
			//is consequence
			window_template.SetIsSecond(true);
		}
		else {
			if (new_operation.GetRuleTemplate().GetSizeOfAntecedent() > 0) {
				window_template.SetIsSecond(true);
			}
			else {
				window_template.SetIsSecond(false);
			}
			window_template.SetIsConsequence(false);
		}
		window_template.SetPreviousItems(temp, window_template.GetIsConsequence(), window_template.GetIsSecond(), new_operation.GetSizeVector());
	}
	//displaying new info page
	if (window_template.GetIsMoveOne()) {
		int loop_size = 6;
		if (window_template.GetIsConsequence()) {
			loop_size = 5;
		}
		for (int i = 0; i < loop_size; i++) {
			new_operation.AddSetData(window_template.GetInfoFromTextField(i), i, window_template.GetHasOperator(), window_template.GetIsConsequence());
		}
		new_operation.AddRule(window_template.GetIsConsequence());
		if (window_template.GetHasOperator()) {
			window_template.ChangeWindowAppearance(true, false, new_operation.GetSizeVector());//is second antecedent
		}
		else if(!window_template.GetIsOperationDone()){
			window_template.ChangeWindowAppearance(true, true, new_operation.GetSizeVector());//is consequence
		}
		else {
			window_template.ChangeWindowAppearance(false, false, new_operation.GetSizeVector());//is antecedent, NEW RULE
		}
	}
}
void LogicHandler::Render() {
	window_template.Render(); 
	if (window_template.GetIsLoadPanel()) {
		help_panel.Render();
		if (help_panel.GetIsGoBack()) {
			window_template.SetIsLoadPanel(false);
		}
	}
	else {
		help_panel.SetIsGoBack(false);
	}
}
void LogicHandler::HandleInput(InputManager input_manger, sf::Event e) {
	window_template.HandleInput(input_manger, e);
	help_panel.Input(input_manger);
}