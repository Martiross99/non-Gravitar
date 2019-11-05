#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "textBox.h"


class fuel {

public:

	fuel();
	~fuel();

	void draw(sf::RenderWindow& window, sf::Vector2f pos);

	float getSize();

	void increase(float x);

	bool decrease();


private:
	sf::RectangleShape contorno;
	sf::RectangleShape carburante;
	textBox testo;
};
