#include "LogicHandler.h"
LogicHandler::LogicHandler(sf::RenderWindow*window,const sf::Font&font ) {
	AddSetUI *temp = new AddSetUI(6, 7, window, false, false, true, font);
	window_template = *temp;
	window_template.SetDisplayText();
}
void LogicHandler::Update() {
	window_template.Update();
	if (window_template.GetIsMoveOne()){
		int loop_size = 6;
		if (window_template.GetIsConsequence()){
			loop_size = 5;
		}
		for (int i = 0; i < loop_size; i++){
			new_operation.AddSetData(window_template.GetInfoFromTextField(i),i, window_template.GetHasOperator());
		}
		new_operation.AddRule(window_template.GetIsConsequence());
		if (window_template.GetHasOperator()){
			window_template.ChangeWindowAppearance(true, false);
		}
		else {
			window_template.ChangeWindowAppearance(true, true);
		}
	}
}
void LogicHandler::Render() {
	window_template.Render();
}
void LogicHandler::HandleInput(InputManager input_manger,sf::Event e) {
	window_template.HandleInput(input_manger,e);
}