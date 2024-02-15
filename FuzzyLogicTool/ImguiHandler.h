#pragma once
#include <SFML/Graphics.hpp>
#include "imgui/imgui.h"
#include "Operation.h"
#include "imgui/imgui-SFML.h"
class ImguiHandler
{
public:
	ImguiHandler(sf::RenderWindow* hwnd);
	void CallUpdate(sf::Clock& delta_clock, const Operation& info, const std::vector<sf::Vector2f> poly_points);
	void Render();
	void Init();
	void InfoToDisplay(const Operation &info, const std::vector<sf::Vector2f> poly_points);
	void ShutDownImgui();
	void ProcessWindow(sf::Event e);
private:
	sf::RenderWindow* window;

};

