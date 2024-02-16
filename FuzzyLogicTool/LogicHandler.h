#pragma once
#include "AddSetUI.h"
#include "Operation.h"
#include "DescriptionInputs.h"
#include "ReviewPanel.h"
#include "InputPanel.h"
#include "DefuzzyCalculator.h"
#include "EditPanel.h"
class LogicHandler
{
public:
	LogicHandler(sf::RenderWindow* window, const sf::Font& font);
	void Update();
	void Render();
	void HandleInput(InputManager input_manger, sf::Event e);
	const Operation GetOperationInfo() const { return new_operation; }
	const std::vector<sf::Vector2f> GetPolyPoints()const;

private:
	std::vector< AddSetUI> set_windows;
	AddSetUI window_template;
	Operation new_operation;
	DescriptionInputs help_panel;
	ReviewPanel review_panel;
	InputPanel input_panel;
	EditPanel edit_panel;
	bool is_added;
	bool is_review_created;
	bool is_input_stage;

	bool is_input_complete;

	int current_display_index;
	std::vector<sf::Vector2f> poly_points;


};

