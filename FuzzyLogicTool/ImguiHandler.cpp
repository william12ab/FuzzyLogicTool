#include "ImguiHandler.h"
ImguiHandler::ImguiHandler(sf::RenderWindow* hwnd) :window(hwnd) {

}
void ImguiHandler::CallUpdate(sf::Clock &delta_clock) {
	ImGui::SFML::Update(*window, delta_clock.restart());
	InfoToDisplay();
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

void ImguiHandler::InfoToDisplay() {
	ImGui::Begin("Options");
	if (ImGui::CollapsingHeader("Rule Info")) {
		for (size_t i = 0; i < 6; i++) {
			std::string s = "If ";
			s.append("temp ");
			s.append("is ");
			s.append("cold ");
			s.append("then ");
			s.append("heat ");
			s.append("is ");
			s.append("warm ");

			ImGui::TextWrapped("s");
			s.clear();
			s.append("Min: ");
			s.append(" 10");
			s.append("Max: ");
			s.append("15");
			s.append("Graph type: ");
			s.append("1");
			s.append("Operator: ");
			s.append("OR");
			ImGui::TextWrapped("Press A to display diagram");
		}
	}
}

void ImguiHandler::ShutDownImgui() {
	ImGui::SFML::Shutdown();

}