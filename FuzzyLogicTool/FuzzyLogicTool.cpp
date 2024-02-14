#include <iostream>
#include "DemoWindow.h"
#include "ImguiHandler.h"
#include <stdio.h>
#include "Input.h"
#include <SFML/Graphics.hpp>
#include "TextFieldObject.h"
#include "InputManager.h"
#include "Operation.h"
#include "AddSetUI.h"
#include "LogicHandler.h"

#include "MathsOperator.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(800, 600), "title");
	sf::Event event;
	ImguiHandler* ui = new ImguiHandler(&window);
	ui->Init();
	sf::Clock delta_clock;
	Input input;
	sf::View view_;
	sf::Font font;
	font.loadFromFile("C:/Windows/Fonts/Arial.ttf");
	view_.reset(sf::FloatRect(0.f, 0.f, (float)window.getSize().x, (float)window.getSize().y));
	InputManager input_manager(&input, &view_, &window);
	LogicHandler program_runner(&window,font);
	bool is_added=false;



	MathsOperator masd;
	sf::Vector2f a(sf::Vector2f(11.f,0.8f));
	sf::Vector2f b(sf::Vector2f(15.f,0.f));
	sf::Vector2f c(sf::Vector2f(10.f,0.f));
	sf::Vector2f d(sf::Vector2f(12.f,0.4f));
	auto asda=masd.intersect(a,b,c,d);

	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			ui->ProcessWindow(event);
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				//window.setView();
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left) {
					//update input class
					input.setMouseLDown(true);
					//std::cout<<"true\n";
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					input.setMouseRDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left) {
					//update input class
					input.setMouseLDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Right) {
					input.setMouseRDown(false);
				}
				break;
			}
		}
		//input
		program_runner.HandleInput(input_manager, event);
		//update
		ui->CallUpdate(delta_clock);
		program_runner.Update();
		//render
		window.clear(sf::Color(255, 255, 255));
		program_runner.Render();
		ui->Render();
		window.display();
	}
	ui->ShutDownImgui();
	delete ui;
	ui = NULL;
	return 0;
}


