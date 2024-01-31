#pragma once
#include <SFML/Graphics.hpp>
class Input
{
private:
	// Mouse structure, store mouse relevant information
	struct Mouse{
		int x, y;
		bool left, right;
	};

public:
	// Functions for setting key as pressed, released and checking current state.
	Input();
	void setKeyDown(int key);
	void setKeyUp(int key);
	bool isKeyDown(int key);

	// Functions are mouse input, including getting and setting current position and mouse button presses.
	void setMouseX(int lx);
	void setMouseY(int ly);
	void setMousePosition(int lx, int ly);
	int getMouseX();
	int getMouseY();
	void setMouseLDown(bool down);
	bool isMouseLDown();
	void setMouseRDown(bool down);
	bool isMouseRDown();

	bool isButtonClicked(sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow& window);
	bool isMouseReleased(sf::RectangleShape object, sf::RenderWindow& window);

private:
	// Array of booleans representing keys (pressed = true, released = false)
	bool keys[256]{ false };
	// Mouse variable
	Mouse mouse;
};
