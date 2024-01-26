#include <iostream>
#include "DemoWindow.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <stdio.h>
#include "Input.h"
#include <SFML/Graphics.hpp>
#include "InputManager.h"


int main(){
	sf::RenderWindow window(sf::VideoMode(800, 600), "title");
	sf::Event event;
	ImGui::SFML::Init(window);
	sf::Clock delta_clock;

    DemoWindow demo;
    //demo.CreateOpertation();
	Input input;
	sf::View view_;
	view_.reset(sf::FloatRect(0.f, 0.f, (float)window.getSize().x, (float)window.getSize().y));
	InputManager input_manager(&input, &view_, &window);




   while (window.isOpen()){
       while (window.pollEvent(event)) {
           ImGui::SFML::ProcessEvent(event);
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
       ImGui::SFML::Update(window, delta_clock.restart());
       ImGui::Begin("Options");
       ImGui::End();
       window.clear(sf::Color(1, 1, 1));
       ImGui::SFML::Render(window);
       window.display();
   }
   ImGui::SFML::Shutdown();
    return 0;
}

