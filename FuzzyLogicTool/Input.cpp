#include "Input.h"

void Input::setKeyDown(int key){
	if (key >= 0){
		keys[key] = true;
	}
}

bool Input::isMouseReleased(sf::RectangleShape object, sf::RenderWindow& window) {
	if (mouse.left){
		sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
		if (tempRect.contains(sf::Mouse::getPosition(window))) {
			mouse.left = false;
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Input::isButtonClicked(sf::RectangleShape object, sf::Mouse::Button button, sf::RenderWindow& window){
	if (sf::Mouse::isButtonPressed(button)){
		sf::IntRect tempRect(object.getPosition().x, object.getPosition().y, object.getGlobalBounds().width, object.getGlobalBounds().height);
		if (tempRect.contains(sf::Mouse::getPosition(window))){
			return true;
		}
	}
	return false;
}

void Input::setKeyUp(int key)
{
	if (key >= 0)
	{
		keys[key] = false;
	}
}

bool Input::isKeyDown(int key)
{
	if (key >= 0)
	{
		return keys[key];
	}
	return false;
}

void Input::setMouseX(int lx)
{
	mouse.x = lx;
}

void Input::setMouseY(int ly)
{
	mouse.y = ly;
}

void Input::setMousePosition(int lx, int ly)
{
	setMouseX(lx);
	setMouseY(ly);
}

int Input::getMouseX()
{
	return mouse.x;
}

int Input::getMouseY()
{
	return mouse.y;
}

void Input::setMouseLDown(bool down)
{
	mouse.left = down;
}
bool Input::isMouseLDown()
{
	return mouse.left;
}

void Input::setMouseRDown(bool down)
{
	mouse.right = down;
}
bool Input::isMouseRDown()
{
	return mouse.right;
}

