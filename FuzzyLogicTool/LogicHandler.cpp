#include "LogicHandler.h"
LogicHandler::LogicHandler(sf::RenderWindow*window,const sf::Font&font ) {
	/*set_windows.push_back(AddSetUI(6, 7, window, false, false, true, font));
	set_windows[0].SetDisplayText();*/

	AddSetUI *temp = new AddSetUI(6, 7, window, false, false, true, font);
	window_template = *temp;
	window_template.SetDisplayText();
}
void LogicHandler::Update() {
	
	if (window_template.GetIsMoveOne()){
		int loop_size = 6;
		if (window_template.GetIsConsequence()){
			loop_size = 5;
		}
		for (int i = 0; i < loop_size; i++){
			new_operation.AddSetData(window_template.GetInfoFromTextField(i),i, window_template.GetIsConsequence());
		}
		new_operation.AddRule(window_template.GetIsConsequence());
	}
}
void LogicHandler::Render() {
	window_template.Render();
}
void LogicHandler::HandleInput(InputManager input_manger,sf::Event e) {
	window_template.HandleInput(input_manger,e);
}