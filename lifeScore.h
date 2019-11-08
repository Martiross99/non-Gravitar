#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "textBox.h"

class lifeScore {

public:

	lifeScore();
	~lifeScore();

	int getLives();  //ritorna il numero di vite ancora disponibili
	void setLives(int n);

	void decreaseLives();  //decremta di uno il numero delle vite

	float getSize();

	void setSize(float x);

	void draw(sf::RenderWindow& window);

private:
	int livesLeft;
	sf::ConvexShape lives;

	sf::RectangleShape lifeBar;
	sf::RectangleShape contorno;

	textBox life;

};
