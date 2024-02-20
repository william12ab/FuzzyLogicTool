#include "ImguiHandler.h"

ImguiHandler::ImguiHandler(sf::RenderWindow* hwnd) :window(hwnd) {

}
void ImguiHandler::CallUpdate(sf::Clock &delta_clock, const Operation& info, const std::vector<sf::Vector2f> poly_points) {
	ImGui::SFML::Update(*window, delta_clock.restart());
	InfoToDisplay(info, poly_points);
	ImGui::End();
}
void ImguiHandler::Render() {
	ImGui::SFML::Render(*window);
}

void ImguiHandler::Init() {
	ImGui::SFML::Init(*window);
}
void ImguiHandler::ProcessWindow(sf::Event e) {
	ImGui::SFML::ProcessEvent(e);
}

void ImguiHandler::InfoToDisplay(const Operation& info, const std::vector<sf::Vector2f> poly_points) {
	ImGui::Begin("Options");
	
	if (ImGui::CollapsingHeader("Rule Info")) {
		for (size_t i = 0; i < info.GetRuleVector().size(); i++) {
			std::string s = "If ";
			for (size_t j = 0; j < info.GetRuleVector()[i].GetAntecedentVector().size(); j++){
				s.append(info.GetRuleVector()[i].GetAntecedentVector()[j].GetxName());
				s.append(" is ");
				s.append(info.GetRuleVector()[i].GetAntecedentVector()[j].GetGraphName());
				ImGui::TextWrapped("%s", s.c_str());

				s.clear();
				s.append("Min: ");
				s.append(std::to_string(info.GetRuleVector()[i].GetAntecedentVector()[j].GetMin()));
				s.append("\nMax: ");
				s.append(std::to_string(info.GetRuleVector()[i].GetAntecedentVector()[j].GetMax()));
				s.append("\nGraph type: ");
				s.append(std::to_string(info.GetRuleVector()[i].GetAntecedentVector()[j].GetGraphType()));
				s.append("\nOperator: ");
				s.append(std::to_string(info.GetRuleVector()[i].GetAntecedentVector()[j].GetOperatorValue()));
				ImGui::TextWrapped("\n%s", s.c_str());
				s.clear();
				s.append("\n");
			}
			s.clear();
			s.append("\nThen ");
			s.append(info.GetRuleVector()[i].GetConsequenceVector()[0].GetxName());
			s.append(" is ");
			s.append(info.GetRuleVector()[i].GetConsequenceVector()[0].GetGraphName());
			s.append("\nMin: ");
			s.append(std::to_string(info.GetRuleVector()[i].GetConsequenceVector()[0].GetMin()));
			s.append("\nMax: ");
			s.append(std::to_string(info.GetRuleVector()[i].GetConsequenceVector()[0].GetMax()));
			ImGui::TextWrapped("%s", s.c_str());
			s.clear();
			s.append("Fuzzy Value: ");
			s.append(std::to_string(info.GetRuleVector()[i].GetOperatorValue()));
			ImGui::TextWrapped("%s", s.c_str());
			s.clear();
		}
	}
	if (ImGui::CollapsingHeader("Polygon Points")){
		for (size_t i = 0; i < poly_points.size(); i++){
			std::string s;
			s.append(std::to_string(poly_points[i].x));
			s.append(" ");
			s.append(std::to_string(poly_points[i].y));
			ImGui::TextWrapped("%s",s.c_str());
		}
	}

}

void ImguiHandler::ShutDownImgui() {
	ImGui::SFML::Shutdown();

}