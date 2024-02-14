#pragma once
#include <SFML/Graphics.hpp>
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
class ImguiHandler
{
public:
	ImguiHandler(sf::RenderWindow* hwnd);
	void CallUpdate(sf::Clock& delta_clock);
	void Render();
	void Init();
	void InfoToDisplay();
	void ShutDownImgui();
	void ProcessWindow(sf::Event e);
private:
	sf::RenderWindow* window;

};

