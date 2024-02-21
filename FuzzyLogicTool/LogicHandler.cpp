#include "LogicHandler.h"
#include <iostream>
LogicHandler::LogicHandler(sf::RenderWindow* window, const sf::Font& font) {
	AddSetUI* temp = new AddSetUI(6, 7, window, false, false, true, font);
	window_template = *temp;

	window_template.SetDisplayText();
	is_added = false;
	DescriptionInputs* temphelp = new DescriptionInputs(font, window);
	help_panel = *temphelp;

	ReviewPanel* tempreview = new ReviewPanel(window, 1, font);
	review_panel = *tempreview;

	InputPanel* tempinput = new InputPanel(1, 1, window, font);
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

	is_gone_back = false;
	is_review_created = false;
	is_input_stage = false;
	is_input_complete = false;
	is_data_need_validate = false;
	current_display_index = 0;
}

void LogicHandler::DisplayOld() {
	is_data_need_validate = true;
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

void LogicHandler::Update() {
	if (!window_template.GetIsFinished()) {
		window_template.Update();
		//displaying old info page
		if (window_template.GetIsGoBack()) {
			DisplayOld();
			is_data_need_validate = true; 
			is_gone_back = true;
		}
		//displaying new info page
		if (window_template.GetIsMoveOne() || window_template.GetIsTriggerIsFinish()) {
			int loop_size = 6;
			if (window_template.GetIsConsequence()) {
				loop_size = 5;
			}
			for (int i = 0; i < loop_size; i++) {
				new_operation.AddSetData(window_template.GetInfoFromTextField(i), i, window_template.GetHasOperator(), window_template.GetIsConsequence());
			}
			if (!window_template.GetIsConsequence()) {
				current_display_index++;
			}
			new_operation.AddRule(window_template.GetIsConsequence(), current_display_index,is_data_need_validate);
			is_data_need_validate = false;
			if (window_template.GetIsTriggerIsFinish()) {
				window_template.SetIsFinished(true);
			}
			else {
				if (is_gone_back){
					current_display_index++;
					is_data_need_validate = true;
					DisplayOld();
					is_gone_back = false;
				}
				else if (window_template.GetHasOperator()) {
					window_template.ChangeWindowAppearance(true, false, new_operation.GetSizeVector());//is second antecedent
				}
				else if (!window_template.GetIsOperationDone()) {
					window_template.ChangeWindowAppearance(true, true, new_operation.GetSizeVector());//is consequence
				}
				else {
					window_template.ChangeWindowAppearance(false, false, new_operation.GetSizeVector());//is antecedent, NEW RULE
					current_display_index = 0;
					window_template.SetIsOperationDone(false);
				}
			}
		}
	}
	else {
		if (!is_review_created) {
			is_review_created = true;
			review_panel.SetText(new_operation.GetRuleVector());
		}
	}
	if (review_panel.GetIsDonePressed() && !is_input_stage) {
		is_input_stage = true;
		input_panel.SetText(new_operation.GetRuleVector());
	}
	if (is_input_stage) {
		if (new_operation.GetRuleVector().size()==1){
			input_panel.SetIsOneRule(true);
		}
		
		input_panel.CheckForInputAdded();
		if (input_panel.GetIsInputAdded() && !is_input_complete) {
			new_operation.PerformOperation(input_panel.GetHumanValues());
			for (int i = 0; i < new_operation.GetRuleVector().size(); i++) {
				input_panel.SetOperatorValues(new_operation.GetRuleVector()[i].GetOperatorValue());
			}
			new_operation.SortPoints();
			DefuzzyCalculator g;
			g.FindPoints(new_operation);
			sf::Vector2f finalvalue;
			if (new_operation.GetRuleVector().size()>1){
				finalvalue= g.FindDefuzzyValue();
			}
			else {
				if (input_panel.GetIsMax()){
					finalvalue = g.FindMaxDefuzzyValue();
				}
				else {
					finalvalue = g.FindMinDeFuzzyValue();
				}
			}
			
			is_input_complete = true;
			input_panel.SetDefuzzyValue(finalvalue.x);
			input_panel.UpdateOperatorText(g.GetPoints());
			poly_points = g.GetPoints();
		}
		if (input_panel.GetIsClear()){
			input_panel.SetIsClear(false);
			input_panel.ClearValues();
			is_input_complete = false;
			new_operation.ClearOperationValues();
		}
	}

	int index = 0;
	for (size_t i = 0; i < review_panel.GetEdit().size(); i++) {
		if (review_panel.GetEdit()[i]) {
			//bring up temp addsetui with that rule data, validate that data when its finished and then either discard or change
			review_panel.SetEditBool(false, i);
			edit_panel.SetInfo(new_operation.GetRuleVector()[i].GetAntecedentVector().size());
			edit_panel.SetInfo(new_operation.GetRuleVector()[i]);
			edit_panel.SetIsEditDisplay(true);
			index = i;
		}
	}
	if (edit_panel.GetIsDonePressed()) {
		Rule temp_rule;
		edit_panel.SetIsDone(false);
		edit_panel.SetIsEditDisplay(false);
		if (edit_panel.CompareInfo(new_operation.GetRuleVector()[index], temp_rule)){
			new_operation.ReplaceData(temp_rule, index);
			is_review_created = false;
		}
		edit_panel.Reset();
	}
}
void LogicHandler::Render() {
	if (!window_template.GetIsFinished()) {
		if (window_template.GetIsLoadPanel()) {
			help_panel.Render();
			if (help_panel.GetIsGoBack()) {
				window_template.SetIsLoadPanel(false);
			}
		}
		else {
			window_template.Render();
			help_panel.SetIsGoBack(false);
		}
	}
	else {
		if (!review_panel.GetIsDonePressed()) {
			if (!edit_panel.GetIsEditDisplay()) {
				if (review_panel.GetIsLoadHelp()) {
					help_panel.Render();
					if (help_panel.GetIsGoBack()) {
						review_panel.SetIsLoadHelp(false);
					}
				}
				else {
					review_panel.Render();
					help_panel.SetIsGoBack(false);
				}
			}
			else {
				if (edit_panel.GetIsEditDisplay()) {
					if (edit_panel.GetIsLoadHelp()) {
						help_panel.Render();
						if (help_panel.GetIsGoBack()) {
							edit_panel.SetIsLoadHelp(false);
						}
					}
					else {
						edit_panel.Render();
						help_panel.SetIsGoBack(false);
					}
				}
			}
		}
		else {
			input_panel.Render();
		}
	}
}
void LogicHandler::HandleInput(InputManager input_manger, sf::Event e) {
	if (!window_template.GetIsFinished()) {
		if (window_template.GetIsLoadPanel()) {
			help_panel.Input(input_manger);
		}
		else {
			window_template.HandleInput(input_manger, e);
		}
	}
	else {
		if (!review_panel.GetIsDonePressed()) {
			if (!edit_panel.GetIsEditDisplay()) {
				if (review_panel.GetIsLoadHelp()) {
					help_panel.Input(input_manger);
				}
				else {
					review_panel.Input(input_manger);
				}
			}
			else if (edit_panel.GetIsEditDisplay()) {
				if (edit_panel.GetIsLoadHelp()) {
					help_panel.Input(input_manger);
				}
				else {
					edit_panel.Input(input_manger,e);
				}
			}
		}
		else {
			input_panel.HandleInput(input_manger, e);
		}
	}
}

const std::vector<sf::Vector2f> LogicHandler::GetPolyPoints() const {
	if (poly_points.size() > 0) {
		return poly_points;
	}
	return std::vector<sf::Vector2f>();
}
