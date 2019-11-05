#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include "textBox.h"


class tank {

public:
	tank();
	~tank();

	void draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f pos);

	sf::Vector2f getPosition();

	void rotate(double rotation);

	float getQuantity();

	void setQuantity(float x);

	int getType();

	void setColor();

	void update();

private:
	sf::RectangleShape serbatoio;
	float quantity;
	textBox testo;
	sf::Font font;

	int type;

};