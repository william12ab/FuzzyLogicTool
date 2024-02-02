#pragma once
#include "AddSetUI.h"
#include "Operation.h"
#include "DescriptionInputs.h"
#include "ReviewPanel.h"
class LogicHandler
{
public:
	LogicHandler(sf::RenderWindow* window, const sf::Font& font);
	void Update();
	void Render();
	void HandleInput(InputManager input_manger, sf::Event e);
private:
	std::vector< AddSetUI> set_windows;
	AddSetUI window_template;
	Operation new_operation;
	DescriptionInputs help_panel;
	ReviewPanel review_panel;
	bool is_added;
	bool is_review_created;
};

