#include "LogicHandler.h"
#include <iostream>
LogicHandler::LogicHandler(sf::RenderWindow* window, const sf::Font& font){
	AddSetUI* temp = new AddSetUI(6, 7, window, false, false, true, font);
	window_template = *temp;
	
	window_template.SetDisplayText();
	is_added = false;
	DescriptionInputs *temphelp = new DescriptionInputs(font, window);
	help_panel = *temphelp;

	ReviewPanel* tempreview = new ReviewPanel(window,1,font);
	review_panel= *tempreview;

	InputPanel* tempinput = new InputPanel(1,1,window, font);
	input_panel = *tempinput;

	EditPanel* tempedit = new EditPanel(window, font);
	edit_panel = *tempedit;

	delete tempedit;
	tempedit = NULL;
	delete tempinput;
	tempinput = NULL;
	delete temp;
	temp = NULL;
	delete temphelp;
	temphelp = NULL;
	delete tempreview;
	tempreview = NULL;

	is_review_created = false;
	is_input_stage = false;
	is_input_complete = false;

	current_display_index = 0;
}
void LogicHandler::Update() {
	if (!window_template.GetIsFinished()) {
		window_template.Update();
		//displaying old info page
		if (window_template.GetIsGoBack()) {
			auto temp = new_operation.GetData(current_display_index);

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
		if (window_template.GetIsMoveOne()|| window_template.GetIsTriggerIsFinish()) {
			int loop_size = 6;
			if (window_template.GetIsConsequence()) {
				loop_size = 5;
			}
			for (int i = 0; i < loop_size; i++) {
				new_operation.AddSetData(window_template.GetInfoFromTextField(i), i, window_template.GetHasOperator(), window_template.GetIsConsequence());
			}
			if (!window_template.GetIsConsequence()){
				current_display_index++;
			}
			new_operation.AddRule(window_template.GetIsConsequence(),current_display_index);
			if (window_template.GetIsTriggerIsFinish()) {
				window_template.SetIsFinished(true);
			}
			else {
				if (window_template.GetHasOperator()) {
					window_template.ChangeWindowAppearance(true, false, new_operation.GetSizeVector());//is second antecedent
				}
				else if (!window_template.GetIsOperationDone()) {
					window_template.ChangeWindowAppearance(true, true, new_operation.GetSizeVector());//is consequence
				}
				else {
					window_template.ChangeWindowAppearance(false, false, new_operation.GetSizeVector());//is antecedent, NEW RULE
					current_display_index=0;
					window_template.SetIsOperationDone(false);
				}
			}
		}
	}
	else {
		if (!is_review_created){
			is_review_created = true;
			review_panel.SetText(new_operation.GetRuleVector());
		}
	}
	if (review_panel.GetIsDonePressed()&& !is_input_stage) {
		is_input_stage = true;
		input_panel.SetText(new_operation.GetRuleVector());
	}
	if (is_input_stage){
		input_panel.CheckForInputAdded();
		if (input_panel.GetIsInputAdded()&& !is_input_complete){
			new_operation.PerformOperation(input_panel.GetHumanValues());
			for (int i = 0; i < new_operation.GetRuleVector().size(); i++){
				input_panel.SetOperatorValues(new_operation.GetRuleVector()[i].GetOperatorValue());
			}
			new_operation.SortPoints();
			DefuzzyCalculator g;
			g.FindPoints(new_operation);
			auto finalvalue=g.FindDefuzzyValue();
			is_input_complete = true;
			input_panel.SetDefuzzyValue(finalvalue.x);
			input_panel.UpdateOperatorText(g.GetPoints());
			poly_points=g.GetPoints();
		}
	}


	for (size_t i = 0; i < review_panel.GetEdit().size(); i++){
		if (review_panel.GetEdit()[i]) {
			//bring up temp addsetui with that rule data, validate that data when its finished and then either discard or change
			review_panel.SetEditBool(false,i);
			edit_panel.SetInfo(new_operation.GetRuleVector()[i].GetAntecedentVector().size());
			edit_panel.SetInfo(new_operation.GetRuleVector()[i]);
			edit_panel.SetIsEditDisplay(true);
		}
	}
}
void LogicHandler::Render() {
	if (!window_template.GetIsFinished()){
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
	else {
		if (!review_panel.GetIsDonePressed()){
			if (review_panel.GetIsLoadHelp()) {
				help_panel.Render();
				if (help_panel.GetIsGoBack()) {
					review_panel.SetIsLoadHelp(false);
				}
			}
			else {
				if (edit_panel.GetIsEditDisplay()) {
					edit_panel.Render();
				}
				else {
					help_panel.SetIsGoBack(false);
					review_panel.Render();
				}
			}
		}
		else {
			input_panel.Render();
		}	
	}
	
}
void LogicHandler::HandleInput(InputManager input_manger, sf::Event e) {
	if (!window_template.GetIsFinished()){
		if (window_template.GetIsLoadPanel()){
			help_panel.Input(input_manger);
		}
		else {
			window_template.HandleInput(input_manger, e);
		}
	}
	else {
		if (!review_panel.GetIsDonePressed()){
			if (review_panel.GetIsLoadHelp()) {
				help_panel.Input(input_manger);
			}
			else {
				review_panel.Input(input_manger);
			}
		}
		else {
			input_panel.HandleInput(input_manger,e);
		}
	}
}

const std::vector<sf::Vector2f> LogicHandler::GetPolyPoints() const{
	if (poly_points.size()>0){
		return poly_points;
	}
	return std::vector<sf::Vector2f>();
}
